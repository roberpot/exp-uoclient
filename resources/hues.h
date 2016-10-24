//
// Created by rot on 21/10/16.
//

#ifndef __UONEWCLIENT_HUES_H
#define __UONEWCLIENT_HUES_H

#include <map>
#include <cstdio>

#include "../common/types.h"
#include "../common/debug.h"

class HuesEntry {
public:
    uo_word colortable[32];
    uo_word tablestart;
    uo_word tableend;
    uo_char name[20];
    HuesEntry();
    void read(FILE * f);
};

class HuesGroup {
public:
    uo_dword header;
    uo_dword entries[8];
    HuesGroup();
    void read(FILE * f);
};

class HuesManager {
public:
    static HuesManager * get();
    void init(const char * findex);
    void halt();
private:
    HuesManager() {}
    HuesManager(const HuesManager &g) { UNREFERENCED_PARAMETER(g); }
    void operator = (const HuesManager & g) { UNREFERENCED_PARAMETER(g); }
    static HuesManager _hm;
    FILE * _findex;
    std::map<uo_dword, HuesGroup> huesgroups;
    std::map<uo_dword, HuesEntry> huesentries;
};

#endif //__UONEWCLIENT_HUES_H
