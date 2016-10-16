//
// Created by rot on 16/10/2016.
//

#include "inputprocessor.h"
#include "../engines/input.h"
#include "physicalcomponent.h"

#include "../common/debug.h"


void InputProcessor::run_tick(unsigned int delay) {
    UNREFERENCED_PARAMETER(delay);
    InputEngine * input = InputEngine::get();
    input->run();
    CAshley::Family f;
    CAshley::EntityArray v;
    f.filter<PhysicalComponent>();
    v = this->_engine->get_entities_for(f);
    for (unsigned int i = 0; i < v.size(); i++) {
        v[i]->get_component<PhysicalComponent>()->run(input);
    }
}
