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


class GumpInfo {
public:

    unsigned int texture, width, height;
    char * raw, * decompressed, * onlygraypixels;
};


class GumpManager : public IndexFile {
public:
    static GumpManager * get();
    void init(const char * findex, const char * fdata);
    void halt();
    bool is_valid_index(uo_dword index);
    char * get_raw_gump(uo_dword index);
    GumpInfo get_gump(uo_dword i, unsigned int forced_color = 0);
//    GumpInfo get_gump__(uo_dword i, HuesEntry hues, bool onlyhuegraypixels, unsigned int forced_color=0);
    unsigned int unload_gump(uo_dword i);
    unsigned int clean_cache();
    unsigned int cache_size() { return _cache_size; }
    unsigned int mem_size() { return _cache_size + _inuse_size; }
private:
    GumpManager() {}
    GumpManager(const GumpManager &g) { UNREFERENCED_PARAMETER(g); }
    void operator = (const GumpManager & g) { UNREFERENCED_PARAMETER(g); }
    GumpInfo _load_gump(uo_dword i, unsigned int forced_color);
    static GumpManager _gm;
    FILE * _findex, * _fdata;
    std::map<uo_dword, GumpInfo> gump_cache, gump_inuse;
    unsigned int _cache_size, _inuse_size;
    /// New imp.
    std::map<uo_dword, char*> _bitmap_cache;
    std::map<uo_dword, bool> _removed;
};

#endif //__UONEWCLIENT_GUMP_H
