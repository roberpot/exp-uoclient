//
// Created by rot on 11/10/16.
//

#include "../../resources/gump.h"

#include "gumppic.h"
#include "../../cashley/visualcomponent.h"

void GumpPic::init(Form * f, uo_dword gumpid, int x, int y, int z) {
    BaseGump::init(f);
    _gump_id = gumpid;

    GumpManager * gumpmanager = GumpManager::get();
    // Graphical component.
    add_component<VisualComponent>();
    GumpInfo ginfo = gumpmanager->get_gump(_gump_id);
    VisualComponent * gcomp = this->get_component<VisualComponent>();
    gcomp->setup(x, y, ginfo.width, ginfo.height, z, ginfo.texture, 0);
    // Physical component.
}

void GumpPic::shutdown() {
//    GumpManager * gumpmanager = GumpManager::get();
//    MemoryManager * memory = MemoryManager::get();
//    memory->graphic_component_deactivate(gc);
//    DEBUG_MSG("INTER MEM.");
//    memory->graphic_component_free(gc);
//    gumpmanager->unload_gump(_gump_id);
}