//
// Created by rot on 12/10/2016.
//

#include "form.h"


Form::Form(CAshley::Engine * engine) {
    _engine = engine;
}

Form::~Form() {
    disable();
    while(_gumps.size()) {
        BaseGump * g = _gumps.back();
        _gumps.pop_back();
        delete g;
    }
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