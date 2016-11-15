//
// Created by rot on 09/11/2016.
//

#ifndef __UONEWCLIENT_TEXTENTRY_H
#define __UONEWCLIENT_TEXTENTRY_H

#include <string>

#include <cashley/cashley.h>
#include <SDL2/SDL_render.h>

#include "../../common/types.h"
#include "../../common/garbagecollector/displaylist.h"
#include "basegump.h"
#include "../inputreader.h"

class TextEntry : public CAshley::Entity, public BaseGump, public InputReader {
public:
    void init(Form * f, unsigned int font, const char * n, const char * t, unsigned int x, unsigned int y, unsigned int w, unsigned int h);
    void init(Form * f, unsigned int font, const char * n, const char * t, unsigned int x, unsigned int y, unsigned int w, unsigned int h, uo_dword huesentry);
    void move(int x, int y, int z);
    void shutdown();
    void left_click();
    ~TextEntry() {}
    void get_char(Key k);
    CASHLEY_ENTITY
protected:
    virtual void _focus();
    virtual void _blur();
    unsigned int _font;
    std::string _buffer;
    ResourceRef<DisplayList> _text;
    int _lx, _ly, _lz;
    uo_dword _hues;
private:
    std::string _name;
};

#endif //__UONEWCLIENT_TEXTENTRY_H
