//
// Created by rot on 16/11/16.
//

#include "button.h"
#include "../../resources/gump.h"
#include "../../cashley/visualcomponent.h"
#include "../../cashley/physicalcomponent.h"


void Button::init(Form * f, uo_dword gumpid, uo_dword gumpover, uo_dword gumpin, unsigned int x, unsigned int y) {    BaseGump::init(f);
    _x = x;
    _y = y;
    _gumpref = gumpmanager[gumpid];
    _gumprefover = gumpmanager[gumpover];
    _gumprefin = gumpmanager[gumpin];
    add_component<VisualComponent>();
    get_component<VisualComponent>()->setup(x, y, _gumpref()->width(), _gumpref()->height(), 0, _gumpref()->texturize(), 0);
    add_component<PhysicalComponent>();
    PhysicalComponent * p = get_component<PhysicalComponent>();
    _color = p->get_color();
    _p_texref = _gumpref()->texturize(_color);
    _p_texrefover = _gumprefover()->texturize(_color);
    _p_texrefin = _gumprefin()->texturize(_color);
    p->setup(x, y, _gumpref()->width(), _gumpref()->height(), 0, _p_texref);
}

void Button::move(int x, int y, int z) {
    get_component<VisualComponent>()->move(x + _x, y + _y, z);
    get_component<PhysicalComponent>()->move(x + _x, y + _y, z);
}

void Button::shutdown() {
    _gumpref = ResourceRef<GumpInfo>();
    _gumprefover = ResourceRef<GumpInfo>();
    _gumprefin = ResourceRef<GumpInfo>();
    _p_texref = ResourceRef<Texture>();
    _p_texrefover = ResourceRef<Texture>();
    _p_texrefin = ResourceRef<Texture>();
}
