//
// Created by rot on 21/10/16.
//

#include "hues.h"
#include "../common/colorutils.h"

HuesEntry::HuesEntry() {
    for (unsigned int i = 0; i < 32; i++) {
        colortable[i] = 0;
    }
    tablestart = 0;
    tableend = 0;
    name[0] = '\000';
}

void HuesEntry::read(FILE * f) {
    fread((void *)colortable, sizeof(uo_word), 32, f);
    fread((void *)&tablestart, sizeof(uo_word), 1, f);
    fread((void *)&tableend, sizeof(uo_word), 1, f);
    fread((void *)name, sizeof(uo_char), 20, f);
    for (unsigned int i = 0; i < 32; i++) {
        uicolortable[i] = color16_to_color32(colortable[i]);
    }
}

HuesGroup::HuesGroup() {
    header = 0;
}

void HuesGroup::read(FILE * f) {
    fread((void *)&header, sizeof(uo_dword), 1, f);
}

HuesManager * HuesManager::get() {
    static HuesManager _hm;
    return &_hm;
}


void HuesManager::init(const char * findex) {
    _findex = fopen(findex, "rb");
    if (_findex == NULL) {
        DEBUG_ERROR("Can not open hues.mul");
        return;
    }
    unsigned int length;
    fseek(_findex, 0, SEEK_END);
    length = (unsigned int)ftell(_findex);
    rewind(_findex);
    if (length % sizeof(HuesGroup) > 0) {
        DEBUG_ERROR("Bad hues size. Extra bytes: " << (length % sizeof(HuesGroup)));
        return;
    }
    DEBUG_MSG("Size of hues.mul: " << length << " bytes. Total colors groups: " << (length / sizeof(HuesGroup)));
    while (! feof(_findex)) {
        uo_dword groupindex = (uo_dword)ftell(_findex);
        HuesGroup huesgroup;
        huesgroup.read(_findex);
        for (unsigned int i = 0; i < 8; i++) {
            HuesEntry huesentry;
            uo_dword huesindex = (uo_dword)ftell(_findex);
            huesentry.read(_findex);
            huesgroup.entries[i] = huesindex;
            huesentries[huesindex] = huesentry;
        }
        huesgroups[groupindex] = huesgroup;
    }
}
