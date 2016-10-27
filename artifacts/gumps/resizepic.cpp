//
// Created by rot on 17/10/2016.
//

#include <GL/gl.h>
#include "resizepic.h"
#include "../../common/utils.h"
#include "../../cashley/visualcomponent.h"
#include "../../cashley/physicalcomponent.h"


void ResizePic::init(Form * f, uo_dword gumpid, int x, int y, int z, int w, int h) {
    BaseGump::init(f);
    GumpManager * gumpmanager = GumpManager::get();
    add_component<VisualComponent>();
    VisualComponent * vcomp = get_component<VisualComponent>();
    for (unsigned int i = 0; i < 9; i++) {
        _ginforefs[i] = gumpmanager->get(gumpid + i);
    }
    _dl = glGenLists(1);
    glNewList(_dl, GL_COMPILE);
    _prerender(w, h);
    glEndList();
    vcomp->setup_with_dl(x, y, z, _dl);
    add_component<PhysicalComponent>();
    PhysicalComponent * pcomp = get_component<PhysicalComponent>();
    _dl2 = glGenLists(1);
    glNewList(_dl2, GL_COMPILE);
    _prerender(w, h, pcomp->get_color());
    glEndList();
    pcomp->setup_with_dl(x, y, z, _dl2);
}

void ResizePic::_prerender(int w, int h, unsigned int color) {
    unsigned int interx1, interx2, intery1, intery2, tmptex[9];
    for (unsigned int i = 0; i < 9; i++) {
        if (color) {
            tmptex[i] = _ginforefs[i].gump()->texturize(color);
        } else {
            _flattextures[i] = tmptex[i] = _ginforefs[i].gump()->texturize();
        }
    }
    interx1 = _ginforefs[0].gump()->width();
    intery1 = _ginforefs[0].gump()->height();
    interx2 = w - _ginforefs[2].gump()->width();
    intery2 = h - _ginforefs[6].gump()->height();
    // Top-left.
    display_textured_square(0, 0, _ginforefs[0].gump()->width(), _ginforefs[0].gump()->height(), 0, tmptex[0]);
    // Top-right.
    display_textured_square(interx2, 0, _ginforefs[2].gump()->width(), _ginforefs[2].gump()->height(), 0, tmptex[2]);
    // Top.
    display_textured_square(interx1, 0, interx2 - interx1, _ginforefs[1].gump()->height(), 0, tmptex[1]);
    // Bottom-left.
    display_textured_square(0, intery2, _ginforefs[6].gump()->width(), _ginforefs[6].gump()->height(), 0, tmptex[6]);
    // Bottom-right.
    display_textured_square(interx2, intery2, _ginforefs[8].gump()->width(), _ginforefs[8].gump()->height(), 0, tmptex[8]);
    // Bottom.
    display_textured_square(interx1, intery2, interx2 - interx1, _ginforefs[7].gump()->height(), 0, tmptex[7]);
    // Left.
    display_textured_square(0, intery1, _ginforefs[3].gump()->width(), intery2 - intery1, 0, tmptex[3]);
    // Right.
    display_textured_square(interx2, intery1, _ginforefs[5].gump()->width(), intery2 - intery1, 0, tmptex[5]);
    // Center
    display_textured_square(interx1, intery1, interx2 - interx1, intery2 - intery1, 0, tmptex[4]);
}

void ResizePic::shutdown() {
    for(unsigned int i = 0; i < 9; i++) {
        _ginforefs[i] = GumpInfoRef();
    }
}