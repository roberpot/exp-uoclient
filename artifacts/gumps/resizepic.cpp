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
    _gump_id = gumpid;
    GumpManager * gumpmanager = GumpManager::get();
    add_component<VisualComponent>();
    VisualComponent * vcomp = get_component<VisualComponent>();
    for (unsigned int i = 0; i < 9; i++) {
        _ginfo[i] = gumpmanager->get_gump(gumpid + i);
    }
    _dl = glGenLists(1);
    glNewList(_dl, GL_COMPILE);
    _prerender(_ginfo, w, h);
    glEndList();
    vcomp->setup_with_dl(x, y, z, _dl);
    add_component<PhysicalComponent>();
    PhysicalComponent * pcomp = get_component<PhysicalComponent>();
    for (unsigned int i = 0; i < 9; i++) {
        _ginfoflat[i] = gumpmanager->get_gump(gumpid + i, pcomp->get_color());
    }
    _dl2 = glGenLists(1);
    glNewList(_dl2, GL_COMPILE);
    _prerender(_ginfoflat, w, h);
    glEndList();
    pcomp->setup_with_dl(x, y, z, _dl2);
}

void ResizePic::_prerender(GumpInfo * ginfo, int w, int h) {
    unsigned int interx1, interx2, intery1, intery2;
    // Top-left.
    interx1 = ginfo[0].width;
    intery1 = ginfo[0].height;
    display_textured_square(0, 0, ginfo[0].width, ginfo[0].height, 0, ginfo[0].texture);
    // Top-right.
    interx2 = w - ginfo[2].width;
    display_textured_square(interx2, 0, ginfo[2].width, ginfo[2].height, 0, ginfo[2].texture);
    // Top.
    display_textured_square(interx1, 0, interx2 - interx1, ginfo[1].height, 0, ginfo[1].texture);
    // Bottom-left.
    intery2 = h - ginfo[6].height;
    display_textured_square(0, intery2, ginfo[6].width, ginfo[6].height, 0, ginfo[6].texture);
    // Bottom-right.
    display_textured_square(interx2, intery2, ginfo[8].width, ginfo[8].height, 0, ginfo[8].texture);
    // Bottom.
    display_textured_square(interx1, intery2, interx2 - interx1, ginfo[7].height, 0, ginfo[7].texture);
    // Left.
    display_textured_square(0, intery1, ginfo[3].width, intery2 - intery1, 0, ginfo[3].texture);
    // Right.
    display_textured_square(interx2, intery1, ginfo[5].width, intery2 - intery1, 0, ginfo[5].texture);
    // Center
    DEBUG_INFO("X: " << interx1 << " Y: " << intery1 << " W: " << (interx2-interx1) << " H: " << (intery2 - intery1) << " TEX W: " << ginfo[4].width << " TEX H: " << ginfo[4].height);
    display_textured_square(interx1, intery1, interx2 - interx1, intery2 - intery1, 0, ginfo[4].texture, ginfo[4].width, ginfo[4].height);
}

void ResizePic::shutdown() {

}