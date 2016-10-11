//
// Created by rot on 10/10/16.
//

#ifndef __UONEWCLIENT_FONT_H
#define __UONEWCLIENT_FONT_H

#include <vector>

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

    unsigned int rasterize(const char * buffer);

private:
    void update_max_height(Glyph * g);

    Glyph ** glyphs;
    unsigned int _max_height, _character_count;
};

class FontManager {
public:
    static FontManager * get();
    void init(const char * file);
    void halt();
    unsigned int rasterize(unsigned int f, const char * buffer);
private:
    FontManager() {}
    FontManager(const FontManager &f) { UNREFERENCED_PARAMETER(f); }
    void operator=(const FontManager &f) { UNREFERENCED_PARAMETER(f); }
    static FontManager _fm;
    std::vector<Font *> fonts;
};

#endif //__UONEWCLIENT_FONT_H
