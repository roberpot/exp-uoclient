//
// Created by rot on 10/10/16.
//

#ifndef __UONEWCLIENT_GUMP_H
#define __UONEWCLIENT_GUMP_H

#include <cstdio>
#include <map>
#include <set>

#include "indexfile.h"
#include "hues.h"
#include "../common/debug.h"
#include "../common/types.h"
#include "../common/garbagecollector/texture.h"
#include "../common/garbagecollector/resourcereferencer.h"


class GumpInfo : public ReferencedResource {
public:
    GumpInfo(uo_byte * raw, uo_dword index, unsigned int width, unsigned int height);
    ~GumpInfo();
    void deflate();
    ResourceRef<Texture> texturize();
    unsigned int texturize(HuesEntry e, bool from_gray=false);
    ResourceRef<Texture> texturize(unsigned int color);
    unsigned int memory();
    inline unsigned int width() { return _width; }
    inline unsigned int height() { return _height; }
    void counter_starts();
    void counter_ends();
    friend class GumpInfoRef;
    friend class GumpManager;
private:
    uo_dword _index;
    ResourceRef<Texture> _t;
    unsigned int _width, _height;
    uo_byte * _raw;
    unsigned int * _decompressed, * _onlygraypixels;
    uo_uword * _readyforhues;
};


extern class GumpManager : public IndexFile {
public:
    GumpManager() {}
    void init(const char * findex, const char * fdata);
    void halt();
    ResourceRef<GumpInfo> operator[](uo_dword index);
    unsigned int clean_cache();
    unsigned int buffer_size() { return _buffer_size; }
    unsigned int mem_size() { return _cache_size + _buffer_size; }
    friend void GumpInfo::counter_starts();
    friend void GumpInfo::counter_ends();
private:
    GumpManager(const GumpManager &g) { UNREFERENCED_PARAMETER(g); }
    void operator = (const GumpManager & g) { UNREFERENCED_PARAMETER(g); }

    virtual bool is_valid_index(uo_dword index);

    bool is_gump_in_buffer(uo_dword index);
    bool is_gump_in_cache(uo_dword index);
    void move_gump_from_buffer_to_cache(uo_dword index);
    void move_gump_from_cache_to_buffer(uo_dword index);

    std::map<uo_dword, GumpInfo *> gump_buffer, gump_cache;
    unsigned int _cache_size, _buffer_size;
} gumpmanager;

#endif //__UONEWCLIENT_GUMP_H
