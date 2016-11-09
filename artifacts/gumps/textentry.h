//
// Created by rot on 09/11/2016.
//

#ifndef __UONEWCLIENT_TEXTENTRY_H
#define __UONEWCLIENT_TEXTENTRY_H

#include <string>

#include <cashley/cashley.h>

#include "../../common/types.h"
#include "../../common/garbagecollector/displaylist.h"
#include "basegump.h"

class TextEntry : public CAshley::Entity, public BaseGump {
public:
    void init(Form * f, unsigned int font, const char * n, const char * t, unsigned int x, unsigned int y, unsigned int w, unsigned int h);
    void init(Form * f, unsigned int font, const char * n, const char * t, unsigned int x, unsigned int y, unsigned int w, unsigned int h, uo_dword huesentry);
    void move(int x, int y, int z);
    void shutdown();
    void left_click();
    ~TextEntry() {}
private:
    int _lx, _ly, _lz;
    unsigned int _font;
    uo_dword _hues;
    std::string _buffer;
    std::string _name;
    ResourceRef<DisplayList> _text;
};

#endif //__UONEWCLIENT_TEXTENTRY_H
