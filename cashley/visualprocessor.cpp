//
// Created by rot on 11/10/16.
//

#include <GL/gl.h>

#include "../engines/video.h"
#include "../common/debug.h"
#include "visualprocessor.h"
#include "visualcomponent.h"


void VisualProcessor::run_tick(unsigned int delay) {
    UNREFERENCED_PARAMETER(delay);
    CAshley::Family f;
    CAshley::EntityArray v;
    f.filter<VisualComponent>();
    v = this->_engine->get_entities_for(f);
    VideoEngine * video = VideoEngine::get();
    video->clear();
    glColor4f(1.0, 1.0, 1.0, 1.0);
    for (unsigned int i = 0; i < v.size(); i++) {
        v[i]->get_component<VisualComponent>()->display();
    }
    video->run();
}