//
// Created by rot on 11/10/16.
//

#include "../resources/gump.h"

#include "gumppic.h"
#include "visualcomponent.h"

void GumpPic::init(uo_dword gumpid, int x, int y, int z) {
    GumpManager * gumpmanager = GumpManager::get();
    add_component<VisualComponent>();
    _gump_id = gumpid;
    GumpInfo ginfo = gumpmanager->get_gump(_gump_id);
    VisualComponent * gcomp = this->get_component<VisualComponent>();
    gcomp->setup(x, y, ginfo.width, ginfo.height, z, ginfo.texture, 0);
}

void GumpPic::shutdown() {
//    GumpManager * gumpmanager = GumpManager::get();
//    MemoryManager * memory = MemoryManager::get();
//    memory->graphic_component_deactivate(gc);
//    DEBUG_MSG("INTER MEM.");
//    memory->graphic_component_free(gc);
//    gumpmanager->unload_gump(_gump_id);
}