//
// Created by rot on 17/10/2016.
//

#include <GL/gl.h>
#include "resizepic.h"
#include "../form.h"
#include "../../common/utils.h"
#include "../../cashley/visualcomponent.h"
#include "../../cashley/physicalcomponent.h"


void ResizePic::init(Form * f, uo_dword gumpid, unsigned int x, unsigned int y, int w, int h) {
    BaseGump::init(f);
    _x = x;
    _y = y;
    add_component<VisualComponent>();
    add_component<PhysicalComponent>();
    VisualComponent * vcomp = get_component<VisualComponent>();
    PhysicalComponent * pcomp = get_component<PhysicalComponent>();
    for (unsigned int i = 0; i < 9; i++) {
        _ginforefs[i] = gumpmanager[gumpid + i];
    }
    _dl = ResourceRef<DisplayList>(new DisplayList);
    _dl()->init_compilation();
    _prerender(w, h);
    _dl()->end_compilation();
    _dl2 = ResourceRef<DisplayList>(new DisplayList);
    _dl2()->init_compilation();
    _prerender(w, h, pcomp->get_color());
    _dl2()->end_compilation();
    vcomp->setup_with_dl(x, y, 0, _dl);
    pcomp->setup_with_dl(x, y, 0, _dl2);
}

void ResizePic::_prerender(int w, int h, unsigned int color) {
    unsigned int interx1, interx2, intery1, intery2;
    ResourceRef<Texture> tmptex[9];
    for (unsigned int i = 0; i < 9; i++) {
        if (color) {
            _flattextures[i] = tmptex[i] = _ginforefs[i]()->texturize(color);
        } else {
            tmptex[i] = _ginforefs[i]()->texturize();
        }
    }
    interx1 = _ginforefs[0]()->width();
    intery1 = _ginforefs[0]()->height();
    interx2 = w - _ginforefs[2]()->width();
    intery2 = h - _ginforefs[6]()->height();
    // Top-left.
    display_textured_square(0, 0, _ginforefs[0]()->width(), _ginforefs[0]()->height(), 0, tmptex[0].get()->get());
    // Top-right.
    display_textured_square(interx2, 0, _ginforefs[2]()->width(), _ginforefs[2]()->height(), 0, tmptex[2].get()->get());
    // Top.
    display_textured_square(interx1, 0, interx2 - interx1, _ginforefs[1]()->height(), 0, tmptex[1].get()->get());
    // Bottom-left.
    display_textured_square(0, intery2, _ginforefs[6]()->width(), _ginforefs[6]()->height(), 0, tmptex[6].get()->get());
    // Bottom-right.
    display_textured_square(interx2, intery2, _ginforefs[8]()->width(), _ginforefs[8]()->height(), 0, tmptex[8].get()->get());
    // Bottom.
    display_textured_square(interx1, intery2, interx2 - interx1, _ginforefs[7]()->height(), 0, tmptex[7].get()->get());
    // Left.
    display_textured_square(0, intery1, _ginforefs[3]()->width(), intery2 - intery1, 0, tmptex[3].get()->get());
    // Right.
    display_textured_square(interx2, intery1, _ginforefs[5]()->width(), intery2 - intery1, 0, tmptex[5].get()->get());
    // Center
    display_textured_square(interx1, intery1, interx2 - interx1, intery2 - intery1, 0, tmptex[4].get()->get(), _ginforefs[4]()->width(), _ginforefs[4]()->height());
}

void ResizePic::move(int x, int y, int z) {
    get_component<VisualComponent>()->move(x + _x, y + _y, z);
    get_component<PhysicalComponent>()->move(x + _x, y + _y, z);
}

void ResizePic::drag(int x, int y) {
    _form->move(x, y);
}

void ResizePic::right_click() {
    _form->close();
}

void ResizePic::shutdown() {
    for(unsigned int i = 0; i < 9; i++) {
        _ginforefs[i] = ResourceRef<GumpInfo>();
        _flattextures[i] = ResourceRef<Texture>();
    }
    _dl = ResourceRef<DisplayList>();
    _dl2 = ResourceRef<DisplayList>();
}
