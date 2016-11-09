//
// Created by rot on 13/10/16.
//

#include <GL/gl.h>

#include "../../resources/gump.h"
#include "../../resources/font.h"

#include "text.h"
#include "../../cashley/visualcomponent.h"
#include "../../cashley/physicalcomponent.h"


void Text::init(Form * f, unsigned int font, const char * t, unsigned int x, unsigned int y) {
    BaseGump::init(f);
    _x = x;
    _y = y;
    // Graphical component.
    add_component<VisualComponent>();
    VisualComponent * vcomp = get_component<VisualComponent>();
    _text = fontmanager.rasterize(font, t);
    vcomp->setup_with_dl(x, y, 0, _text);
}

void Text::init(Form * f, unsigned int font, std::string t, unsigned int x, unsigned int y) {
    init(f, font, t.c_str(), x, y);
}

void Text::move(int x, int y, int z) {
    get_component<VisualComponent>()->move(x + _x, y + _y, z);
}


void Text::init(Form * f, unsigned int font, const char * t, unsigned int x, unsigned int y, uo_dword huesentry) {
    BaseGump::init(f);
    _x = x;
    _y = y;
    // Graphical component.
    add_component<VisualComponent>();
    VisualComponent * vcomp = get_component<VisualComponent>();
    _text = fontmanager.rasterize(font, t, huesentry);
    vcomp->setup_with_dl(x, y, 0, _text);
}

void Text::init(Form * f, unsigned int font, std::string t, unsigned int x, unsigned int y, uo_dword huesentry) {
    init(f, font, t.c_str(), x, y, huesentry);
}

void Text::shutdown() {
    _text = ResourceRef<DisplayList>();
}