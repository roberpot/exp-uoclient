//
// Created by rot on 16/10/2016.
//

#include "../engines/input.h"
#include "../common/debug.h"
#include "inputprocessor.h"
#include "physicalcomponent.h"

void InputProcessor::run_tick(unsigned int delay) {
    UNUSED_PARAMETER(delay);
    CAshley::Family f;
    CAshley::EntityArray v;
    f.filter<PhysicalComponent>();
    v = this->_engine->get_entities_for(f);
    input.run();
    for (unsigned int i = 0; i < v.size(); i++) {
        v[i]->get_component<PhysicalComponent>()->run();
    }
}
