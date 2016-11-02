//
// Created by rot on 13/10/16.
//

#include <SDL2/SDL.h>

#include "input.h"
#include "video.h"
#include "../common/utils.h"


void InputEngine::init_subsystem() {
    _continue_execution = true;
    _collide_color = 0;
    _mouse_status = 0;
    _x = 0;
    _y = 0;
}

void InputEngine::halt_subsystem() {

}

void InputEngine::run() {
    // message processing loop
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        // check for messages
        switch (event.type) {
            case SDL_QUIT:
                _continue_execution = false;
                break;
            case SDL_KEYDOWN: {
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    _continue_execution = false;
                } break;
            }
        } // end switch
    } // end of message processing
    int old_x = _x, old_y = _y;
    unsigned int buttons = SDL_GetMouseState(&_x, &_y);
    _x_run = _x - old_x;
    _y_run = _y - old_y;
    unsigned short old_status = _mouse_status;
    if (buttons & SDL_BUTTON(SDL_BUTTON_LEFT)) {
        UNSET_FLAG(_mouse_status, INPUT_LRELEASE);
        SET_FLAG(_mouse_status, INPUT_LBUTTON);
        if (!(old_status & INPUT_LBUTTON)) {
            SET_FLAG(_mouse_status, INPUT_LCLICK);
        } else {
            UNSET_FLAG(_mouse_status, INPUT_LCLICK);
        }
    } else {
        UNSET_FLAG(_mouse_status, INPUT_LBUTTON);
        UNSET_FLAG(_mouse_status, INPUT_LCLICK);
        if (old_status & INPUT_LBUTTON) {
            SET_FLAG(_mouse_status, INPUT_LRELEASE);
        } else {
            UNSET_FLAG(_mouse_status, INPUT_LRELEASE);
        }
    }
    if (buttons & SDL_BUTTON(SDL_BUTTON_MIDDLE)) {
        UNSET_FLAG(_mouse_status, INPUT_MRELEASE);
        SET_FLAG(_mouse_status, INPUT_MBUTTON);
        if (!(old_status & INPUT_MBUTTON)) {
            SET_FLAG(_mouse_status, INPUT_MCLICK);
        } else {
            UNSET_FLAG(_mouse_status, INPUT_MCLICK);
        }
    } else {
        UNSET_FLAG(_mouse_status, INPUT_MBUTTON);
        UNSET_FLAG(_mouse_status, INPUT_MCLICK);
        if (old_status & INPUT_MBUTTON) {
            SET_FLAG(_mouse_status, INPUT_MRELEASE);
        } else {
            UNSET_FLAG(_mouse_status, INPUT_MRELEASE);
        }
    }
    if (buttons & SDL_BUTTON(SDL_BUTTON_RIGHT)) {
        UNSET_FLAG(_mouse_status, INPUT_RRELEASE);
        SET_FLAG(_mouse_status, INPUT_RBUTTON);
        if (!(old_status & INPUT_RBUTTON)) {
            SET_FLAG(_mouse_status, INPUT_RCLICK);
        } else {
            UNSET_FLAG(_mouse_status, INPUT_RCLICK);
        }
    } else {
        UNSET_FLAG(_mouse_status, INPUT_RBUTTON);
        UNSET_FLAG(_mouse_status, INPUT_RCLICK);
        if (old_status & INPUT_RBUTTON) {
            SET_FLAG(_mouse_status, INPUT_RRELEASE);
        } else {
            UNSET_FLAG(_mouse_status, INPUT_RRELEASE);
        }
    }
    _ticks_update = SDL_GetTicks();
    _collide_color = video.get_collor_at_position(_x, _y);
}
