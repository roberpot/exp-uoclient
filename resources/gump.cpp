#include <iostream>
#include <cstring>
#include <iomanip>

#include <SDL2/SDL.h>
#include <GL/gl.h>

#include "../common/colorutils.h"
#include "../common/textureutils.h"
#include "gump.h"

GumpInfo::GumpInfo(uo_byte * raw, uo_dword index, unsigned int width, unsigned int height) {
    _raw = raw;
    _index = index;
    _width = width;
    _height = height;
    _decompressed = NULL;
    _onlygraypixels = NULL;
    _counter = 0;
    _texture = 0;
}

GumpInfo::~GumpInfo() {
    delete _raw;
    if (_decompressed)
        delete _decompressed;
    if (_onlygraypixels)
        delete _onlygraypixels;
    if (_texture) {
        glDeleteTextures(1, &_texture);
    }
}

void GumpInfo::deflate() {
    unsigned int size = _width * _height;
    _decompressed = new unsigned int[size];
    _onlygraypixels = new unsigned int[size];
    DEBUG_INFO("W: " << _width << " H: " << _height << " SIZE: " << size);
//    uo_char * colortable = new uo_char[128];
    // pshuecolors = hue.colors.
//    uo_char * pbcolortable = colortable;
    // phuecolors = pshuecolors;
    // phuecolorsend = phuecolors + 32;
//    unsigned short * pcolortable = (unsigned short *)pbcolortable;
//    unsigned short * pcolortableopaque = pcolortable;
//    UNREFERENCED_PARAMETER(pcolortableopaque);
    // while (phuecolors < phuecolorsend) {
    //     *pcolortableopaque++ = *phuecolors++;
    // }
    unsigned int * current_target_pixel = _decompressed;
    unsigned int * last_target_pixel = current_target_pixel + size;
    uo_byte * current_source_pixel = _raw;
    unsigned short run = 0;
    unsigned short source_color = 0;
    unsigned int target_color = 0;
    while (current_target_pixel < last_target_pixel) {
        source_color = *(unsigned short *)current_source_pixel;
        current_source_pixel += 2;
        run = *(unsigned short *)current_source_pixel;
        current_source_pixel += 2;
//        if (source_color != 0) {
//            source_color = pcolortable[color >> 10];
//        }
        target_color = color16_to_color32(source_color);
        if (target_color) {
            target_color |= 0xFF000000;
        }
        while (run) {
            *current_target_pixel++ = target_color;
            run--;
        }
    }
}

unsigned int GumpInfo::texturize() {
    if (_texture) {
        return _texture;
    }
    _texture = generate_texture_from_raw(_width, _height, _decompressed);
    return _texture;
}

unsigned int GumpInfo::texturize(HuesEntry e, bool from_gray) {
    UNREFERENCED_PARAMETER(e);
    UNREFERENCED_PARAMETER(from_gray);
    return 0;
}

unsigned int GumpInfo::texturize(unsigned int color) {
    unsigned int size = _width * _height;
    unsigned int * raw_colorized = new unsigned int [size];
    memcpy(raw_colorized, _decompressed, sizeof(unsigned int) * size);
    for (unsigned int i = 0; i < size; i++) {
        if (raw_colorized[i]) {
            raw_colorized[i] = color;
        }
    }
    unsigned int texture = generate_texture_from_raw(_width, _height, raw_colorized);
    delete raw_colorized;
    return texture;
}

unsigned int GumpInfo::memory() {
    return _width * _height * 8; // 4 bytes per color and 2 raw images.
}

//
//void GumpInfo::unload() {
//
//}
//
//void GumpInfo::unload(HuesEntry e, bool from_gray) {
//
//}

void GumpInfo::increase_counter() {
    _counter++;
    if (_counter == 1) {
        GumpManager::get()->move_gump_from_cache_to_buffer(_index);
    }
}

void GumpInfo::decrease_counter() {
    _counter--;
    if (_counter == 0) {
        GumpManager::get()->move_gump_from_buffer_to_cache(_index);
    }
}


GumpInfoRef::GumpInfoRef() {
    _g = NULL;
}

GumpInfoRef::GumpInfoRef(GumpInfo * g) {
    _g = g;
    if (_g) {
        _g->increase_counter();
    }
}

//GumpInfoRef::GumpInfoRef(const GumpInfoRef g) {
//    _g = g._g;
//    if (_g) {
//        _g->increase_counter();
//    }
//}

GumpInfoRef::GumpInfoRef(const GumpInfoRef & g) {
    _g = g._g;
    if (_g) {
        _g->increase_counter();
    }
}

GumpInfoRef & GumpInfoRef::operator=(GumpInfoRef g) {
    _g = g._g;
    if (_g) {
        _g->increase_counter();
    }
    return *this;
}

GumpInfoRef::~GumpInfoRef() {
    if (_g) {
        _g->decrease_counter();
    }
}

GumpInfoRef::operator GumpInfo&() {
    if (_g) {
        return *_g;
    }
    throw 1234;
}


GumpInfoRef::operator bool() const {
    return _g != NULL;
}



GumpManager * GumpManager::get() {
    static GumpManager _gm;
    return &_gm;
}

void GumpManager::init(const char * findex, const char * fdata) {
    _cache_size = 0;
    _buffer_size = 0;
    IndexFile::init(findex, fdata);
}

void GumpManager::halt() {
    IndexFile::halt();
}

bool GumpManager::is_valid_index(uo_dword index) {
    if (! IndexFile::is_valid_index(index)) {
        return false;
    }

    Entry3D e = get_entry(index);

    if (e.extra == -1) {
        return false;
    }

    int width = (e.extra >> 16) & 0xFFFF;
    int height = e.extra & 0xFFFF;
    if (width <= 0 || height <= 0) {
        return false;
    }

    return true;
}


GumpInfoRef GumpManager::operator[](uo_dword index) {
    if (!is_valid_index(index)) {
        DEBUG_ERROR("Invalid index: " << index);
        return NULL;
    }

    if (is_gump_in_buffer(index)) {
        return GumpInfoRef(gump_buffer[index]);
    }
    if (is_gump_in_cache(index)) {
        return GumpInfoRef(gump_cache[index]);
    }

    DEBUG_ERROR("Need to load: " << index);
    Entry3D e = get_entry(index);
    int width = (e.extra >> 16) & 0xFFFF;
    int height = e.extra & 0xFFFF;
    uo_byte * buffer = new uo_byte[e.length];
    read(buffer, e);
    GumpInfo * gump = new GumpInfo(buffer, index, (unsigned int)width, (unsigned int)height);
    gump->deflate();
    gump_cache[index] = gump;
    _buffer_size += gump->memory();
    GumpInfoRef gumpref(gump);
    return gumpref;
}


unsigned int GumpManager::clean_cache() {
    unsigned int cs = _cache_size;
    for (std::map<uo_dword, GumpInfo *>::iterator i = gump_cache.begin(); i != gump_cache.end(); i++) {
        delete i->second;
    }
    _cache_size = 0;
    gump_cache.clear();
    return cs;
}

//GumpInfo GumpManager::_load_gump(uo_dword i, unsigned int forced_color) {
//    GumpIdxEntry entry(_findex, i);
//    uo_byte * gumpdata = new uo_byte[entry.length];
//    fseek(_fdata, entry.lookup, 0);
//    uo_byte raw[4];
//    uo_uword counter = 0;
//    uo_color readed_color= 0;
//    unsigned int color = 0;
//    unsigned int index = 0;
//    unsigned int computed_size = 0;
//    int length_readed = fread(gumpdata, sizeof(uo_byte), entry.length, _fdata);
//    if (length_readed != entry.length) {
//        throw 'a';
//    }
//    unsigned int * rawsurface = new unsigned int[entry.width * entry.height];
//
//    for(int k = 0; k < (entry.height * entry.width); k++) {
//        while (counter == 0) {
//            memcpy(raw, &(gumpdata[index]), 4);
//            //print_raw(raw, 4);
//            memcpy(&readed_color, raw, sizeof(uo_uword));
//            memcpy(&counter, &raw[2], sizeof(uo_uword));
//            color = color16_to_color32(readed_color);
//            if (forced_color != 0 && color != 0) {
//                color = forced_color;
//            }
//            if (color) {
//                color |= 0xFF000000;
//            }
//            index += 4;
//            computed_size += counter;
//        }
//        rawsurface[k] = color;
//        counter--;
//    }
//    delete gumpdata;
//    GumpInfo gump_info;
//    gump_info.texture = generate_texture_from_raw(entry.width, entry.height, rawsurface);
//    gump_info.width = entry.width;
//    gump_info.height = entry.height;
//    gump_info.memory = (unsigned int)(entry.width * entry.height * 4);
//    delete rawsurface;
//    return gump_info;
//}


bool GumpManager::is_gump_in_buffer(uo_dword index) {
    return gump_buffer.count(index) > 0;
}

bool GumpManager::is_gump_in_cache(uo_dword index) {
    return gump_cache.count(index) > 0;
}

void GumpManager::move_gump_from_buffer_to_cache(uo_dword index) {
    GumpInfo * gump = gump_buffer[index];
    gump_cache[index] = gump;
    gump_buffer.erase(index);
    _buffer_size -= gump->memory();
    _cache_size += gump->memory();
}

void GumpManager::move_gump_from_cache_to_buffer(uo_dword index) {
    GumpInfo * gump = gump_cache[index];
    gump_buffer[index] = gump;
    gump_cache.erase(index);
    _cache_size -= gump->memory();
    _buffer_size += gump->memory();
}
