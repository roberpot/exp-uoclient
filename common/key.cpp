//
// Created by rot on 14/11/16.
//

#include "key.h"


Key::Key(SDL_Keycode _k) {
    _key = _k;
    SDL_Keymod mod = SDL_GetModState();
    _ctrl = mod & (KMOD_LCTRL | KMOD_RCTRL);
    _alt = mod & (KMOD_LALT | KMOD_RALT);
    _shift = mod & (KMOD_LSHIFT | KMOD_RSHIFT);
    _v = (char)_k;
    if (_v >= SDLK_a && _v <= SDLK_z) {
        if (_shift != (mod & KMOD_CAPS)) {
            _v += 32;
        }
    }
}

Key::Key(const Key & k) {
    _key = k._key;
    _ctrl = k._ctrl;
    _alt = k._alt;
    _shift = k._shift;
    _v = k._v;
}

Key Key::operator=(Key k) {
    _key = k._key;
    _ctrl = k._ctrl;
    _alt = k._alt;
    _shift = k._shift;
    _v = k._v;
    return *this;
}

Key::operator char() {
    return _v;
}