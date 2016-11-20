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
    add_component<PhysicalComponent>();
    PhysicalComponent * p = get_component<PhysicalComponent>();
    _color = p->get_color();
    _p_texref = _gumpref()->texturize(_color);
    _p_texrefover = _gumprefover()->texturize(_color);
    _p_texrefin = _gumprefin()->texturize(_color);
    _change_to_blur();
}

void Button::move(int x, int y, int z) {
    _lx = x;
    _ly = y;
    _lz = z;
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

void Button::over() {
    _change_to_over();
}

void Button::blur() {
    _change_to_blur();
}

void Button::left_down() {
    _change_to_pushed();
}

void Button::left_up() {
    _change_to_blur();
}

void Button::_change_to_blur() {
    VisualComponent * v = get_component<VisualComponent>();
    v->shutdown();
    v->init();
    v->setup(_x, _y, _gumpref()->width(), _gumpref()->height(), 0, _gumpref()->texturize(), 0);
    move(_lx, _ly, _lz);
    PhysicalComponent * p = get_component<PhysicalComponent>();
    p->shutdown();
    p->init(false);
    p->setup(_x, _y, _gumpref()->width(), _gumpref()->height(), 0, _p_texref);
    move(_lx, _ly, _lz);
}

void Button::_change_to_over() {
    VisualComponent * v = get_component<VisualComponent>();
    v->shutdown();
    v->init();
    v->setup(_x, _y, _gumprefover()->width(), _gumprefover()->height(), 0, _gumprefover()->texturize(), 0);
    move(_lx, _ly, _lz);
    PhysicalComponent * p = get_component<PhysicalComponent>();
    p->shutdown();
    p->init(false);
    p->setup(_x, _y, _gumprefover()->width(), _gumprefover()->height(), 0, _p_texrefover);
    move(_lx, _ly, _lz);
}

void Button::_change_to_pushed() {
    VisualComponent * v = get_component<VisualComponent>();
    v->shutdown();
    v->init();
    v->setup(_x, _y, _gumprefin()->width(), _gumprefin()->height(), 0, _gumprefin()->texturize(), 0);
    move(_lx, _ly, _lz);
    PhysicalComponent * p = get_component<PhysicalComponent>();
    p->shutdown();
    p->init(false);
    p->setup(_x, _y, _gumprefin()->width(), _gumprefin()->height(), 0, _p_texrefin);
    move(_lx, _ly, _lz);
}
