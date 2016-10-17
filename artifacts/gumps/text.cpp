//
// Created by rot on 13/10/16.
//

#include <GL/gl.h>

#include "../../resources/gump.h"
#include "../../resources/font.h"

#include "text.h"
#include "../../cashley/visualcomponent.h"
#include "../../cashley/physicalcomponent.h"


void Text::init(Form * f, unsigned int font, const char * t, int x, int y, int z) {
    BaseGump::init(f);

    // Graphical component.
    add_component<VisualComponent>();
    VisualComponent * vcomp = get_component<VisualComponent>();
    _text = FontManager::get()->rasterize(font, t);
    vcomp->setup_with_dl(x, y, z, _text);
    // Physical component.
    // Physical component.
//    add_component<PhysicalComponent>();
//    this->get_component<PhysicalComponent>()->init();
}

void Text::init(Form * f, unsigned int font, std::string t, int x, int y, int z) {
    init(f, font, t.c_str(), x, y, z);
}

void Text::shutdown() {
    glDeleteLists(_text, 1);
}