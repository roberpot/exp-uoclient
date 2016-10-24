#include <iostream>
#include <cstring>
#include <iomanip>

#include <SDL2/SDL.h>
#include <GL/gl.h>

#include "../common/colorutils.h"
#include "../common/textureutils.h"
#include "gump.h"

GumpInfo::GumpInfo(uo_char * raw, uo_dword index, unsigned int width, unsigned int height) {
    _raw = raw;
    _index = index;
    _width = width;
    _height = height;
    _decompressed = new unsigned int[width * height];
    _onlygraypixels = new unsigned int[width * height];
}

GumpInfo::~GumpInfo() {

}

void GumpInfo::decompress() {

}

unsigned int GumpInfo::texturize() {

}

unsigned int GumpInfo::texturize(HuesEntry e, bool from_gray) {

}

unsigned int GumpInfo::texturize(unsigned int color) {

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
        GumpManager::_gm.move_gump_from_cache_to_buffer(_index);
    }
}

void GumpInfo::decrease_counter() {
    _counter--;
    if (_counter == 0) {
        GumpManager::_gm.move_gump_from_buffer_to_cache(_index);
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

GumpInfoRef::GumpInfoRef(GumpInfoRef & g) {
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

GumpInfo & GumpInfoRef::operator->() {
    if (_g) {
        return *_g;
    }
    throw 1234;
}

bool GumpInfoRef::is_null() {
    return _g == NULL;
}


GumpManager * GumpManager::get() {
    static GumpManager _gm;
    return &_gm;
}

void GumpManager::init(const char * findex, const char * fdata) {
    _cache_size = 0;
    _inuse_size = 0;
    IndexFile::init(findex, fdata);
}

void GumpManager::halt() {
    IndexFile::halt();
}

bool GumpManager::is_valid_index(uo_dword index) {
    if (!IndexFile::is_valid_index(index)) {
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

//char * get_raw_gump(uo_dword index) {}


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

//    Entry3D e = get_entry(index);
//    int width = (e.extra >> 16) & 0xFFFF;
//    int height = e.extra & 0xFFFF;
//    uo_char * buffer = new uo_char[e.length];
//    read(&buffer, e);
//    GumpInfoData gump = new GumpInfo(buffer, (unsigned int)width, (unsigned int)height);
//    gump->decompress();
//    gump_cache[index] = gump;
//    return gump;
//
//    if (forced_color > 0) {
//        return _load_gump(i, forced_color);
//    }
//    // First check if gump is loaded.
//    if (gump_inuse.count(i) == 1) {
//        return gump_inuse[i];
//    }
//    if (gump_cache.count(i) == 1) {
//        GumpInfo gump_info = gump_cache[i];
//        gump_cache.erase(i);
//        gump_inuse[i] = gump_info;
//        _cache_size -= gump_info.memory;
//        _inuse_size += gump_info.memory;
//        return gump_info;
//    }
//    GumpInfo gump_info = _load_gump(i, 0);
//    _inuse_size += gump_info.memory;
//    return gump_info;
}

//unsigned int GumpManager::unload_gump(uo_dword i) {
//    if (gump_inuse.count(i) != 1) {
//        return 1;
//    }
//    GumpInfo gump_info = gump_inuse[i];
//    gump_inuse.erase(i);
//    gump_cache[i] = gump_info;
//    _cache_size += gump_info.memory;
//    _inuse_size -= gump_info.memory;
//    return 0;
//}

unsigned int GumpManager::clean_cache() {
    unsigned int cs = _cache_size;
//    for (std::map<uo_dword, GumpInfo>::iterator i = gump_cache.begin(); i != gump_cache.end(); i++) {
//        remove_texture(i->second.texture);
//    }
//    _cache_size = 0;
//    gump_cache.clear();
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
    gump_cache[index] = gump_buffer[index];
    gump_buffer.erase(index);
}

void GumpManager::move_gump_from_cache_to_buffer(uo_dword index) {
    gump_buffer[index] = gump_cache[index];
    gump_cache.erase(index);
}
