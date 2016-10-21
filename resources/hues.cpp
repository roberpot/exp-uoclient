//
// Created by rot on 21/10/16.
//

#include "hues.h"



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
    length = ftell(_findex);
    rewind(_findex);
    if (length % sizeof(HuesGroup) > 0) {
        DEBUG_ERROR("Bad hues size. Extra bytes: " << (length % sizeof(HuesGroup)));
        return;
    }
}
