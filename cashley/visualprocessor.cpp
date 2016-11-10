//
// Created by rot on 11/10/16.
//

#include <GL/gl.h>

#include "../engines/video.h"
#include "../common/debug.h"
#include "visualprocessor.h"
#include "visualcomponent.h"
#include "../common/utils.h"

void VisualProcessor::run_tick(unsigned int delay) {
    UNUSED_PARAMETER(delay);
    CAshley::Family f;
    CAshley::EntityArray v;
    f.filter<VisualComponent>();
    v = this->_engine->get_entities_for(f);
    video.clear();
    glColor4f(1.0, 1.0, 1.0, 1.0);
    for (unsigned int i = 0; i < v.size(); i++) {
        v[i]->get_component<VisualComponent>()->display();
    }
//    video.clear();
//    float c[4] = {1.0, 0.0, 0.0, 1.0};
//    display_colored_square(333, 348, 200, 22, -2000, c);
    video.run();
}