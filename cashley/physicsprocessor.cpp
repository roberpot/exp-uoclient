//
// Created by rot on 13/10/2016.
//

#include "physicsprocessor.h"
#include "physicalcomponent.h"


void PhysicsProcessor::run_tick(unsigned int delay) {
    UNREFERENCED_PARAMETER(delay);
    CAshley::Family f;
    CAshley::EntityArray v;
    f.filter<PhysicalComponent>();
    v = this->_engine->get_entities_for(f);

}