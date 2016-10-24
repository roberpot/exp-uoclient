//
// Created by rot on 24/10/16.
//

#ifndef __UONEWCLIENT_INDEXFILE_H
#define __UONEWCLIENT_INDEXFILE_H

#include <cstdio>
#include "entry3d.h"
#include "../common/types.h"

class IndexFile {
public:
    IndexFile();
    virtual void init(const char * idxfile, const char * mulfile);
    virtual bool is_valid_index(uo_dword index);
    Entry3D get_entry(uo_dword index);
protected:
    FILE * _mulfile;
private:
    static unsigned int _file_len(FILE * f);
    unsigned int _idxlen, _mullen, _count;
    Entry3D * _index;
    FILE * _idxfile;
};

#endif //__UONEWCLIENT_INDEXFILE_H
