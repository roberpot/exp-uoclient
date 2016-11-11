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

ResourceRef<Texture> GumpInfo::texturize() {
    if (_t.get()) {
        return _t;
    }
    _t = ResourceRef<Texture>(new Texture(_width, _height, _decompressed));
    return _t;
}

ResourceRef<Texture> GumpInfo::texturize(uo_dword huesentry, bool from_gray) {
    HuesEntry hue = huesmanager[huesentry];
    UNUSED_PARAMETER(hue);
    UNUSED_PARAMETER(from_gray);
    return 0;
}

ResourceRef<Texture> GumpInfo::texturize(unsigned int color) {
    unsigned int size = _width * _height;
    unsigned int * raw_colorized = new unsigned int [size];
    memcpy(raw_colorized, _decompressed, sizeof(unsigned int) * size);
    for (unsigned int i = 0; i < size; i++) {
        if (raw_colorized[i]) {
            raw_colorized[i] = color;
        }
    }
    ResourceRef<Texture> t(new Texture(_width, _height, raw_colorized));
    delete raw_colorized;
    return t;
}

unsigned int GumpInfo::memory() {
    return _width * _height * 8; // 4 bytes per color and 2 raw images.
}

void GumpInfo::counter_starts() {
    gumpmanager.move_gump_from_cache_to_buffer(_index);
}

void GumpInfo::counter_ends() {
    gumpmanager.move_gump_from_buffer_to_cache(_index);
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


ResourceRef<GumpInfo> GumpManager::operator[](uo_dword index) {
    if (!is_valid_index(index)) {
        DEBUG_ERROR("Invalid index: " << index);
        return NULL;
    }

    if (is_gump_in_buffer(index)) {
        return ResourceRef<GumpInfo>(gump_buffer[index]);
    }
    if (is_gump_in_cache(index)) {
        return ResourceRef<GumpInfo>(gump_cache[index]);
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
    return ResourceRef<GumpInfo>(gump);
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
