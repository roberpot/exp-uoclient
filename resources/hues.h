//
// Created by rot on 21/10/16.
//

#ifndef __UONEWCLIENT_HUES_H
#define __UONEWCLIENT_HUES_H

#include "../common/types.h"
#include "../common/debug.h"

class HuesEntry {
public:
    uo_word colortable[32];
    uo_word tablestart;
    uo_word tableend;
    uo_char name[20];
};

class HuesGroup {
public:
    uo_dword header;
    HuesEntry entries[8];
};

class HuesManager {
public:
    static HuesManager * get();
    void init(const char * findex);
    void halt();
//    GumpInfo get_gump(uo_dword i, unsigned int forced_color = 0);
//    unsigned int unload_gump(uo_dword i);
//    unsigned int clean_cache();
//    unsigned int cache_size() { return _cache_size; }
//    unsigned int mem_size() { return _cache_size + _inuse_size; }
private:
    HuesManager() {}
    HuesManager(const HuesManager &g) { UNREFERENCED_PARAMETER(g); }
    void operator = (const HuesManager & g) { UNREFERENCED_PARAMETER(g); }
//    GumpInfo _load_gump(uo_dword i, unsigned int forced_color);
    static HuesManager _hm;
    FILE * _findex;
//    std::map<uo_dword, GumpInfo> gump_cache, gump_inuse;
//    unsigned int _cache_size, _inuse_size;
};

#endif //__UONEWCLIENT_HUES_H
