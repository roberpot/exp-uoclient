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
    _readyforhues = NULL;
    _counter = 0;
    _texture = 0;
}

GumpInfo::~GumpInfo() {
    delete _raw;
    if (_decompressed)
        delete _decompressed;
    if (_onlygraypixels)
        delete _onlygraypixels;
    if (_readyforhues) {
        delete _readyforhues;
    }
    if (_texture) {
        glDeleteTextures(1, &_texture);
    }
}

void GumpInfo::deflate() {
    unsigned int size = _width * _height;
    _decompressed = new unsigned int[size];
    _onlygraypixels = new unsigned int[size];
    _readyforhues = new uo_uword[size];
    unsigned int * current_target_pixel = _decompressed;
    unsigned int * current_onlygray_pixel = _onlygraypixels;
    uo_uword * current_readyforhues_pixel = _readyforhues;
    unsigned int * last_target_pixel = current_target_pixel + size;
    uo_byte * current_source_pixel = _raw + sizeof(int) * _height;
    unsigned short run = 0;
    unsigned short source_color = 0;
    unsigned int target_color = 0;
    unsigned int target_onlygray_color = 0;
    uo_uword target_readyforhues_color = 0;
    while (current_target_pixel < last_target_pixel) {
        source_color = *(unsigned short *)current_source_pixel;
        current_source_pixel += 2;
        run = *(unsigned short *)current_source_pixel;
        current_source_pixel += 2;
        target_readyforhues_color = 0;
        target_color = color16_to_color32(source_color);
        if (target_color) {
            target_color |= 0xFF000000;
            target_readyforhues_color = get_huetable_lookup(source_color);
        }
        target_onlygray_color = target_color;
        if (is_gray(source_color)) {
            target_onlygray_color = color16_to_color32_gray(source_color);
        }

        while (run) {
            *current_target_pixel++ = target_color;
            *current_onlygray_pixel++ = target_onlygray_color;
            *current_readyforhues_pixel++ = target_readyforhues_color;
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
    if (_g == g) {
        return;
    }
    _g = g;
    if (_g) {
        _g->increase_counter();
    }
}

GumpInfoRef::GumpInfoRef(const GumpInfoRef & g) {
    if (this == &g) {
        return;
    }
    _g = g._g;
    if (_g) {
        _g->increase_counter();
    }
}

GumpInfoRef & GumpInfoRef::operator=(GumpInfoRef g) {
    if ((this == &g) || (_g == g._g)) {
        return *this;
    }
    if (_g) {
        _g->decrease_counter();
    }
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

GumpInfo * GumpInfoRef::gump() {
    if (_g) {
        return _g;
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
    clean_cache();
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


GumpInfoRef GumpManager::get(uo_dword index) {
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
    Entry3D e = get_entry(index);
    int width = (e.extra >> 16) & 0xFFFF;
    int height = e.extra & 0xFFFF;
    uo_byte * buffer = new uo_byte[e.length];
    read(buffer, e);
    GumpInfo * gump = new GumpInfo(buffer, index, (unsigned int)width, (unsigned int)height);
    gump->deflate();
    gump_cache[index] = gump;
    _cache_size += gump->memory();
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
