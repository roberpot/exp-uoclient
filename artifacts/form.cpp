//
// Created by rot on 12/10/2016.
//

#include "../common/core.h"


Form::Form(CAshley::Engine * engine, uo_char flags) {
    _engine = engine;
    _uid = core.add_form(this);
    _flags = flags;
    _x = 0;
    _y = 0;
    _z = 0;
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
    _z = core.enable_form(_uid);
    for (unsigned int i = 0; i < _gumps.size(); i++) {
        dynamic_cast<CAshley::Entity *>(_gumps[i])->activate();
        _gumps[i]->move(_x, _y, _z - i);
    }
}

void Form::disable() {
    for (unsigned int i = 0; i < _gumps.size(); i++) {
        dynamic_cast<CAshley::Entity *>(_gumps[i])->deactivate();
    }
}

void Form::close() {
    if (!(_flags & FORM_FLAG_NOCLOSE)) {
        disable();
    }
}

void Form::move(int x, int y) {
    bool redraw = false;
    if (!(_flags & FORM_FLAG_NOMOVE)) {
        _x += x;
        _y += y;
        redraw = true;
    }
    if (!core.is_focused(_z)) {
        _z = core.focus(_z);
        redraw = true;
    }
    if (redraw) {
        for (unsigned int i = 0; i < _gumps.size(); i++) {
            _gumps[i]->move(_x, _y, _z - i);
        }
    }
}