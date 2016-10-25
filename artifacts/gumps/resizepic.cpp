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
        _ginforefs[i] = (*gumpmanager)[gumpid + i];
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
            tmptex[i] = static_cast<GumpInfo&>(_ginforefs[i]).texturize(color);
        } else {
            _flattextures[i] = tmptex[i] = static_cast<GumpInfo&>(_ginforefs[i]).texturize();
        }
    }
    interx1 = static_cast<GumpInfo&>(_ginforefs[0]).width();
    intery1 = static_cast<GumpInfo&>(_ginforefs[0]).height();
    interx2 = w - static_cast<GumpInfo&>(_ginforefs[2]).width();
    intery2 = h - static_cast<GumpInfo&>(_ginforefs[6]).height();
    // Top-left.
    display_textured_square(0, 0, static_cast<GumpInfo&>(_ginforefs[0]).width(), static_cast<GumpInfo&>(_ginforefs[0]).height(), 0, tmptex[0]);
    // Top-right.
    display_textured_square(interx2, 0, static_cast<GumpInfo&>(_ginforefs[2]).width(), static_cast<GumpInfo&>(_ginforefs[2]).height(), 0, tmptex[2]);
    // Top.
    display_textured_square(interx1, 0, interx2 - interx1, static_cast<GumpInfo&>(_ginforefs[1]).height(), 0, tmptex[1]);
    // Bottom-left.
    display_textured_square(0, intery2, static_cast<GumpInfo&>(_ginforefs[6]).width(), static_cast<GumpInfo&>(_ginforefs[6]).height(), 0, tmptex[6]);
    // Bottom-right.
    display_textured_square(interx2, intery2, static_cast<GumpInfo&>(_ginforefs[8]).width(), static_cast<GumpInfo&>(_ginforefs[8]).height(), 0, tmptex[8]);
    // Bottom.
    display_textured_square(interx1, intery2, interx2 - interx1, static_cast<GumpInfo&>(_ginforefs[7]).height(), 0, tmptex[7]);
    // Left.
    display_textured_square(0, intery1, static_cast<GumpInfo&>(_ginforefs[3]).width(), intery2 - intery1, 0, tmptex[3]);
    // Right.
    display_textured_square(interx2, intery1, static_cast<GumpInfo&>(_ginforefs[5]).width(), intery2 - intery1, 0, tmptex[5]);
    // Center
    display_textured_square(interx1, intery1, interx2 - interx1, intery2 - intery1, 0, tmptex[4]);
}

void ResizePic::shutdown() {

}