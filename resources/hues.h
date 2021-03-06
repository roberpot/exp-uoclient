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
    unsigned int uicolortable[32];
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

extern class HuesManager {
public:
    HuesManager() {}
    void init(const char * findex);
    void halt();
    HuesEntry operator[](uo_dword i);
private:
    HuesManager(const HuesManager &g) { UNUSED_PARAMETER(g); }
    void operator = (const HuesManager & g) { UNUSED_PARAMETER(g); }
    FILE * _findex;
    std::map<uo_dword, HuesGroup> huesgroups;
    std::map<uo_dword, HuesEntry> huesentries;
} huesmanager;

#endif //__UONEWCLIENT_HUES_H
