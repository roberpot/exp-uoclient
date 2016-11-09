//
// Created by rot on 09/11/2016.
//

#include "textentry.h"


#include "../../resources/font.h"
#include "../../cashley/visualcomponent.h"
#include "../../cashley/physicalcomponent.h"


void TextEntry::init(Form * f, unsigned int font, const char * n, const char * t, unsigned int x, unsigned int y, unsigned int w, unsigned int h) {
    BaseGump::init(f);
    _x = x;
    _y = y;
    _name = n;
    _buffer = t;
    _font = font;
    _hues = -1;
    // Graphical component.
    add_component<VisualComponent>();
    VisualComponent * vcomp = get_component<VisualComponent>();
    _text = fontmanager.rasterize(font, t);
    vcomp->setup_with_dl(x, y, 0, _text);
    // Physical component.
    add_component<PhysicalComponent>();
    PhysicalComponent * pcomp = get_component<PhysicalComponent>();
    pcomp->setup(x, y, w, h, 0, PC_F_DISPLAY_FLAT);
}

void TextEntry::init(Form * f, unsigned int font, const char * n, const char * t, unsigned int x, unsigned int y, unsigned int w, unsigned int h, uo_dword huesentry) {
    BaseGump::init(f);
    _x = x;
    _y = y;
    _name = n;
    _buffer = t;
    _font = font;
    _hues = huesentry;
    // Graphical component.
    add_component<VisualComponent>();
    VisualComponent * vcomp = get_component<VisualComponent>();
    _text = fontmanager.rasterize(font, t, huesentry);
    vcomp->setup_with_dl(x, y, 0, _text);
    // Physical component.
    add_component<PhysicalComponent>();
    PhysicalComponent * pcomp = get_component<PhysicalComponent>();
    pcomp->setup(x, y, w, h, 0, PC_F_DISPLAY_FLAT);
}

void TextEntry::move(int x, int y, int z) {
    _lx = x;
    _ly = y;
    _lz = z;
    get_component<VisualComponent>()->move(x + _x, y + _y, z);
    get_component<PhysicalComponent>()->move(x + _x, y + _y, z);
}

void TextEntry::left_click() {
    if (_hues == -1) {
        _text = fontmanager.rasterize(_font, (_buffer + '_').c_str());
    } else {
        _text = fontmanager.rasterize(_font, (_buffer + '_').c_str(), _hues);
    }
    VisualComponent * vcomp = get_component<VisualComponent>();
    vcomp->shutdown();
    vcomp->setup_with_dl(_x, _y, 0, _text);
    move(_lx, _ly, _lz);
}

void TextEntry::shutdown() {
    _text = ResourceRef<DisplayList>();
}