//
// Created by rot on 11/10/16.
//

#include "../../resources/gump.h"

#include "gumppic.h"
#include "../../cashley/visualcomponent.h"
#include "../../cashley/physicalcomponent.h"
#include "../form.h"

void GumpPic::init(Form * f, uo_dword gumpid, unsigned int x, unsigned int y) {
    BaseGump::init(f);
    _x = x;
    _y = y;
    _gumpref = gumpmanager[gumpid];
        // Graphical component.
    add_component<VisualComponent>();
    get_component<VisualComponent>()->setup(x, y, _gumpref()->width(), _gumpref()->height(), 0, _gumpref()->texturize(), 0);
    // Physical component.
    add_component<PhysicalComponent>();
    get_component<PhysicalComponent>()->setup(x, y, _gumpref()->width(), _gumpref()->height(), 0, _gumpref()->texturize(get_component<PhysicalComponent>()->get_color()));
}

void GumpPic::move(int x, int y, int z) {
    get_component<VisualComponent>()->move(x + _x, y + _y, z);
    get_component<PhysicalComponent>()->move(x + _x, y + _y, z);
}

void GumpPic::drag(int x, int y) {
    _form->move(x, y);
}

void GumpPic::right_click() {
    _form->close();
}

void GumpPic::shutdown() {
    _gumpref = ResourceRef<GumpInfo>();
}
