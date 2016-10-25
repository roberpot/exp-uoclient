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
    GumpInfo(uo_byte * raw, uo_dword index, unsigned int width, unsigned int height);
    ~GumpInfo();
    void deflate();
    unsigned int texturize();
    unsigned int texturize(HuesEntry e, bool from_gray=false);
    unsigned int texturize(unsigned int color);
    unsigned int memory();
    inline unsigned int width() { return _width; }
    inline unsigned int height() { return _height; }
//    void unload();
//    void unload(HuesEntry e, bool from_gray=false);
    friend class GumpInfoRef;
    friend class GumpManager;
private:
    void increase_counter();
    void decrease_counter();
    uo_dword _index;
    unsigned int _texture, _width, _height;
    unsigned int _counter;
    uo_byte * _raw;
    unsigned int * _decompressed, * _onlygraypixels;
};


class GumpInfoRef {
public:
    GumpInfoRef();
    GumpInfoRef(GumpInfo * g);
//    GumpInfoRef(const GumpInfoRef g);
    GumpInfoRef(const GumpInfoRef & g);
    GumpInfoRef & operator=(GumpInfoRef g);
    ~GumpInfoRef();
    operator GumpInfo&();
    operator bool() const;
private:
    GumpInfo * _g;
};


class GumpManager : public IndexFile {
public:
    static GumpManager * get();
    void init(const char * findex, const char * fdata);
    void halt();
    GumpInfoRef operator[](uo_dword index);
    unsigned int clean_cache();
    unsigned int cache_size() { return _cache_size; }
    unsigned int mem_size() { return _cache_size + _buffer_size; }
    friend void GumpInfo::increase_counter();
    friend void GumpInfo::decrease_counter();
private:
    GumpManager() {}
    GumpManager(const GumpManager &g) { UNREFERENCED_PARAMETER(g); }
    void operator = (const GumpManager & g) { UNREFERENCED_PARAMETER(g); }
    static GumpManager _gm;
    virtual bool is_valid_index(uo_dword index);

    bool is_gump_in_buffer(uo_dword index);
    bool is_gump_in_cache(uo_dword index);
    void move_gump_from_buffer_to_cache(uo_dword index);
    void move_gump_from_cache_to_buffer(uo_dword index);

    std::map<uo_dword, GumpInfo *> gump_buffer, gump_cache;
    unsigned int _cache_size, _buffer_size;
};

#endif //__UONEWCLIENT_GUMP_H
