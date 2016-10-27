//
// Created by rot on 11/10/16.
//

#include "../../resources/gump.h"

#include "gumppic.h"
#include "../../cashley/visualcomponent.h"
#include "../../cashley/physicalcomponent.h"

void GumpPic::init(Form * f, uo_dword gumpid, int x, int y, int z) {
    BaseGump::init(f);

    GumpManager * gumpmanager = GumpManager::get();
    _gumpref = gumpmanager->get(gumpid);
        // Graphical component.
    add_component<VisualComponent>();
    get_component<VisualComponent>()->setup(x, y, _gumpref.gump()->width(), _gumpref.gump()->height(), z, _gumpref.gump()->texturize(), 0);
    // Physical component.
    add_component<PhysicalComponent>();
    get_component<PhysicalComponent>()->setup(x, y, _gumpref.gump()->width(), _gumpref.gump()->height(), z, _gumpref.gump()->texturize(get_component<PhysicalComponent>()->get_color()));
}

void GumpPic::shutdown() {
    _gumpref = GumpInfoRef();
//    GumpManager * gumpmanager = GumpManager::get();
//    MemoryManager * memory = MemoryManager::get();
//    memory->graphic_component_deactivate(gc);
//    DEBUG_MSG("INTER MEM.");
//    memory->graphic_component_free(gc);
//    gumpmanager->unload_gump(_gump_id);
}