//
// Created by rot on 10/10/16.
//

#ifndef __UONEWCLIENT_GUMP_H
#define __UONEWCLIENT_GUMP_H

#include <cstdio>
#include <map>
#include <set>

#include "../common/types.h"


class GumpInfo {
public:
    unsigned int memory, texture, width, height;
};


class GumpManager {
public:
    static GumpManager * get();
    void init(const char * findex, const char * fdata);
    void halt();
    GumpInfo get_gump(uo_dword i);
    unsigned int unload_gump(uo_dword i);
    unsigned int clean_cache();
    unsigned int cache_size() { return _cache_size; }
    unsigned int mem_size() { return _cache_size + _inuse_size; }
private:
    GumpManager() {}
    GumpManager(const GumpManager &g) {}
    void operator = (const GumpManager & g) {}
    GumpInfo _load_gump(uo_dword i);
    static GumpManager _gm;
    FILE * _findex, * _fdata;
    std::map<uo_dword, GumpInfo> gump_cache, gump_inuse;
    unsigned int _cache_size, _inuse_size;
};

#endif //__UONEWCLIENT_GUMP_H
