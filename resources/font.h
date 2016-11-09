//
// Created by rot on 10/10/16.
//

#ifndef __UONEWCLIENT_FONT_H
#define __UONEWCLIENT_FONT_H

#include <vector>

#include "hues.h"
#include "../common/garbagecollector/displaylist.h"
#include "../common/debug.h"

class Glyph;

class Font {
public:
    Font(unsigned int character_count=224);
    ~Font();

    class Reference {
        friend class Font;
        Reference(Font * f, unsigned int i);
        Font * _f;
        unsigned int _i;
    public:
        ~Reference() {};
        Reference& operator=(Glyph * g);
        Reference& operator=(const Reference& x);
    };

    Glyph * operator[](unsigned int i) const;
    Reference operator[](unsigned int i);

    ResourceRef<DisplayList> rasterize(const char * buffer);
    ResourceRef<DisplayList> rasterize(const char * buffer, uo_dword huesentry);

private:
    void update_max_height(Glyph * g);

    Glyph ** glyphs;
    unsigned int _max_height, _character_count;
};

extern class FontManager {
public:
    FontManager() {}
    void init(const char * file);
    void halt();
    ResourceRef<DisplayList> rasterize(unsigned int f, const char * buffer);
    ResourceRef<DisplayList> rasterize(unsigned int f, const char * buffer, uo_dword huesentry);
private:
    FontManager(const FontManager &f) { UNUSED_PARAMETER(f); }
    void operator=(const FontManager &f) { UNUSED_PARAMETER(f); }
    std::vector<Font *> fonts;
} fontmanager;

#endif //__UONEWCLIENT_FONT_H
