//
// Created by rot on 13/10/2016.
//

#include "../common/debug.h"
#include "../engines/video.h"
#include "physicsprocessor.h"
#include "physicalcomponent.h"


void PhysicsProcessor::run_tick(unsigned int delay) {
    UNREFERENCED_PARAMETER(delay);
    CAshley::Family f;
    CAshley::EntityArray v;
    f.filter<PhysicalComponent>();
    v = this->_engine->get_entities_for(f);
    video.clear();
    for (unsigned int i = 0; i < v.size(); i++) {
        v[i]->get_component<PhysicalComponent>()->display();
    }
}