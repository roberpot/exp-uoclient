//
// Created by rot on 12/10/2016.
//

#include "form.h"


Form::Form(CAshley::Engine * engine) {
    _engine = engine;
}

void Form::addgump(BaseGump * g) {
    _engine->add_entity(dynamic_cast<CAshley::Entity *>(g));
    _gumps.push_back(g);
}

void Form::enable() {
    for (unsigned int i = 0; i < _gumps.size(); i++) {
        dynamic_cast<CAshley::Entity *>(_gumps[i])->activate();
    }
}

void Form::disable() {
    for (unsigned int i = 0; i < _gumps.size(); i++) {
        dynamic_cast<CAshley::Entity *>(_gumps[i])->deactivate();
    }
}