#include <iostream>
#include <cstring>
#include <iomanip>

#include <SDL2/SDL.h>
#include <GL/gl.h>

#include "../common/colorutils.h"
#include "../common/textureutils.h"
#include "gump.h"

#define GUMP_INDEX_ENTRY_SIZE 12


class GumpIdxEntry {
public:
    uo_dword lookup, length;
    uo_uword height, width;
    uo_byte * entry;
    GumpIdxEntry(FILE * f, uo_dword i);
    ~GumpIdxEntry();
};

GumpIdxEntry::GumpIdxEntry(FILE * f, uo_dword i) {
    lookup = 0;
    length = 0;
    width = 0;
    height = 0;
    entry = new uo_byte[GUMP_INDEX_ENTRY_SIZE];
    fseek(f, i * GUMP_INDEX_ENTRY_SIZE, 0);
    unsigned int res = fread(entry, sizeof(uo_byte), GUMP_INDEX_ENTRY_SIZE, f);
    if (res != (GUMP_INDEX_ENTRY_SIZE * sizeof(uo_byte))) {
        throw 1;
    }
    //print_raw(entry, GUMP_INDEX_ENTRY_SIZE);

    memcpy(&lookup, entry, sizeof(uo_dword));
    memcpy(&length, &entry[4], sizeof(uo_dword));
    memcpy(&height, &entry[8], sizeof(uo_uword));
    memcpy(&width, &entry[10], sizeof(uo_uword));
}

GumpIdxEntry::~GumpIdxEntry() {
    delete entry;
}

GumpManager * GumpManager::get() {
    static GumpManager _gm;
    return &_gm;
}

void GumpManager::init(const char * findex, const char * fdata) {
    _findex = fopen(findex, "rb");
    _fdata = fopen(fdata, "rb");
    _cache_size = 0;
    _inuse_size = 0;
}

void GumpManager::halt() {
    fclose(_findex);
    fclose(_fdata);
}

GumpInfo GumpManager::get_gump(uo_dword i, unsigned int forced_color) {
    if (forced_color > 0) {
        return _load_gump(i, forced_color);
    }
    // First check if gump is loaded.
    if (gump_inuse.count(i) == 1) {
        return gump_inuse[i];
    }
    if (gump_cache.count(i) == 1) {
        GumpInfo gump_info = gump_cache[i];
        gump_cache.erase(i);
        gump_inuse[i] = gump_info;
        _cache_size -= gump_info.memory;
        _inuse_size += gump_info.memory;
        return gump_info;
    }
    GumpInfo gump_info = _load_gump(i, 0);
    _inuse_size += gump_info.memory;
    return gump_info;
}

unsigned int GumpManager::unload_gump(uo_dword i) {
    if (gump_inuse.count(i) != 1) {
        return 1;
    }
    GumpInfo gump_info = gump_inuse[i];
    gump_inuse.erase(i);
    gump_cache[i] = gump_info;
    _cache_size += gump_info.memory;
    _inuse_size -= gump_info.memory;
    return 0;
}

unsigned int GumpManager::clean_cache() {
    unsigned int cs = _cache_size;
    for (std::map<uo_dword, GumpInfo>::iterator i = gump_cache.begin(); i != gump_cache.end(); i++) {
        remove_texture(i->second.texture);
    }
    _cache_size = 0;
    gump_cache.clear();
    return cs;
}

GumpInfo GumpManager::_load_gump(uo_dword i, unsigned int forced_color) {
    GumpIdxEntry entry(_findex, i);
    uo_byte * gumpdata = new uo_byte[entry.length];
    fseek(_fdata, entry.lookup, 0);
    uo_byte raw[4];
    uo_uword counter = 0;
    uo_color readed_color= 0;
    unsigned int color = 0;
    unsigned int index = 0;
    unsigned int computed_size = 0;
    int length_readed = fread(gumpdata, sizeof(uo_byte), entry.length, _fdata);
    if (length_readed != entry.length) {
        throw 'a';
    }
    unsigned int * rawsurface = new unsigned int[entry.width * entry.height];

    for(int k = 0; k < (entry.height * entry.width); k++) {
        while (counter == 0) {
            memcpy(raw, &(gumpdata[index]), 4);
            //print_raw(raw, 4);
            memcpy(&readed_color, raw, sizeof(uo_uword));
            memcpy(&counter, &raw[2], sizeof(uo_uword));
            color = (unsigned int)color16_to_color32(readed_color);
            if (forced_color != 0 && color != 0) {
                color = forced_color;
            }
            if (color) {
                color |= 0xFF000000;
            }
            index += 4;
            computed_size += counter;
        }
        rawsurface[k] = color;
        counter--;
    }
    delete gumpdata;
    GumpInfo gump_info;
    gump_info.texture = generate_texture_from_raw(entry.width, entry.height, rawsurface);
    gump_info.width = entry.width;
    gump_info.height = entry.height;
    gump_info.memory = entry.width * entry.height * 4;
    delete rawsurface;
    return gump_info;
}
