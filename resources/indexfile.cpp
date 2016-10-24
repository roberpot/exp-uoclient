//
// Created by rot on 24/10/16.
//

#include "../common/debug.h"
#include "indexfile.h"


unsigned int IndexFile::_file_len(FILE * f) {
    fseek(f, 0L, SEEK_END);
    unsigned int sz = (unsigned int)ftell(f);
    fseek(f, 0L, SEEK_SET);
    return sz;
}


IndexFile::IndexFile() {
    _idxfile = NULL;
    _mulfile = NULL;
    _idxlen = 0;
    _mullen = 0;
    _count = 0;
    _index = NULL;
}


void IndexFile::init(const char * idxfile, const char * mulfile) {
    _idxfile = fopen(idxfile, "rb");
    if (!_idxfile) {
        DEBUG_ERROR("Can not open .idx file: " << idxfile);
        throw 1;
    }
    _mulfile = fopen(mulfile, "rb");
    if (!_mulfile) {
        DEBUG_ERROR("Can not open .mul file: " << mulfile);
        throw 1;
    }
    _idxlen = _file_len(_idxfile);
    _mullen = _file_len(_mulfile);
    _count = _idxlen / 12;
    _index = new Entry3D[_count];
    fread((void*)_index, _idxlen, 1, _idxfile);
}

bool IndexFile::is_valid_index(uo_dword index) {
    if (index < 0 || (unsigned int)index >= _count) {
        return false;
    }
    Entry3D e = _index[index];
    if (e.lookup < 0) {
        return false;
    }

    e.length &= 0x7FFFFFFF;

    if ((e.length & (1 << 31)) != 0) {
        // patched ?
        return true;
    }

    if (e.length < 0) {
        return false;
    }

    if (_mullen < (unsigned int)e.lookup) {
        return false;
    }

    // not patched.
    return true;
}

Entry3D IndexFile::get_entry(uo_dword index) {
    if (!is_valid_index(index)) {
        DEBUG_ERROR("Index not valid: " << index);
        throw 1;
    }
    Entry3D e = _index[index];
    // Always not patched.
    return e;
}