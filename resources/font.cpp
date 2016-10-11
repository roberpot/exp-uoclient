//
// Created by rot on 10/10/16.
//

#include <GL/gl.h>

#include "../common/colorutils.h"
#include "../common/debug.h"
#include "../common/errors.h"
#include "../common/textureutils.h"
#include "../common/types.h"
#include "../common/utils.h"
#include "font.h"

class Glyph {
public:
    Glyph() {}
    Glyph(uo_byte w, uo_byte h, uo_byte header, unsigned int * pixels);
    ~Glyph();
    void render(int x, int y);
    unsigned int w() { return (unsigned int)_w; }
    unsigned int h() { return (unsigned int)_h; }
private:
    uo_byte _w, _h, _header;
    unsigned int texture;
};

Glyph::Glyph(uo_byte w, uo_byte h, uo_byte header, unsigned int * pixels) {
    _w = w;
    _h = h;
    _header = header;
    texture = generate_texture_from_raw(_w, _h, pixels);
}

Glyph::~Glyph() {
    remove_texture(texture);
}

void Glyph::render(int x, int y) {
    display_textured_square(x, y, _w, _h, 0, texture);
}

Font::Reference::Reference(Font * f, unsigned int i) {
    _f = f;
    _i = i;
}

Font::Reference& Font::Reference::operator=(Glyph * g) {
    _f->glyphs[_i] = g;
    _f->update_max_height(g);
    return *this;
}

Font::Reference& Font::Reference::operator=(const Font::Reference& x) {
    if (_f != x._f) {
        throw 1;
    }
    _f->glyphs[_i] = x._f->glyphs[x._i];
    return *this;
}

Font::Font(unsigned int character_count) {
    glyphs = new Glyph *[character_count];
    _character_count = character_count;
    _max_height = 0;
}

Font::~Font() {
    for (unsigned int i = 0; i < _character_count; i++) {
        delete glyphs[i];
    }
    delete glyphs;
}

Glyph * Font::operator[](unsigned int i) const {
    return glyphs[i];
}

Font::Reference Font::operator[](unsigned int i) {
    Font::Reference r(this, i);
    return r;
}

void Font::update_max_height(Glyph * g) {
    if (g->h() > _max_height) {
        _max_height = g->h();
    }
}

unsigned int Font::rasterize(const char * buffer) {
    unsigned int displaylist_id = glGenLists(1);
    unsigned int index = 0;
    glNewList(displaylist_id, GL_COMPILE);
    for(unsigned int i = 0; i < strlen(buffer); i++) {
        Glyph * g = glyphs[buffer[i] - 32];
        g->render(index, _max_height - g->h());
        index += g->w();
    }
    glEndList();
    return displaylist_id;
}

FontManager * FontManager::get() {
    static FontManager _fm;
    return &_fm;
}

void FontManager::init(const char * file) {
    FILE * f = fopen(file, "rb");
    if (!f) {
        DEBUG_ERROR("No encuentro el fichero de fuentes " << file);
        FileError e("Fichero de fuentes no encontrado.");
        throw e;
    }
    unsigned int bytes_readed = 0;
    uo_byte w, h, header;
    uo_color * pixels;
    unsigned int * pixels32;
    unsigned int current_color;
    fseek(f, 1, SEEK_SET);
    while(!feof(f)) {
        Font * font = new Font;
        DEBUG_MSG("Reading font " << fonts.size());
        for(unsigned int i = 0; i < 224; i++) {
            w = fgetc(f);
            h = fgetc(f);
            header = fgetc(f);
            DEBUG_MSG("Glyph " << i << " CP: " << ftell(f) << " W: " << (int)w << " H: " << (int)h << " Header: " << (int)header);
            pixels = new uo_color[w * h];
            pixels32 = new unsigned int[w * h];

            bytes_readed = fread(pixels, sizeof(uo_color), w * h, f);
            if (bytes_readed != (unsigned int)(w * h)) {
                DEBUG_WARNING("Readed: " << bytes_readed << " Needed: " << (w * h));
            }
            for (unsigned int j = 0; j < (unsigned int)(w * h); j++) {
                current_color = color16_to_color32(pixels[j]);
                if (!current_color) {
                    current_color = 0x000000FF;
                }
                pixels32[j] = current_color;

            }
            Glyph * g = new Glyph(w, h, header, pixels32);
            (*font)[i] = g;
            delete pixels;
            delete pixels32;
        }
        fonts.push_back(font);
        // Discard a char.
        fgetc(f);
    }
    fclose(f);
    DEBUG_MSG("Readed " << fonts.size() << " fonts.");
}

void FontManager::halt() {
    for(unsigned int i = 0; i < fonts.size(); i++) {
        delete fonts[i];
    }
    fonts.clear();
}

unsigned int FontManager::rasterize(unsigned int f, const char * buffer) {
    return fonts[f]->rasterize(buffer);
}