//
// Created by rot on 13/10/16.
//

#include <GL/gl.h>

#include "../../resources/gump.h"
#include "../../resources/font.h"

#include "text.h"
#include "../../cashley/visualcomponent.h"


void Text::init(Form * f, unsigned int font, const char * t, int x, int y, int z) {
    BaseGump::init(f);

    // Graphical component.
    add_component<VisualComponent>();
    VisualComponent * gcomp = this->get_component<VisualComponent>();
    _text = FontManager::get()->rasterize(font, t);
    gcomp->setup_with_dl(x, y, z, _text);
    // Physical component.
}

void Text::init(Form * f, unsigned int font, std::string t, int x, int y, int z) {
    init(f, font, t.c_str(), x, y, z);
}

void Text::shutdown() {
    glDeleteLists(_text, 1);
}