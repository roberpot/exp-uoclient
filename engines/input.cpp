//
// Created by rot on 13/10/16.
//

#include <SDL2/SDL.h>

#include "input.h"
#include "video.h"


InputEngine::InputEngine() {
    _continue_execution = true;
    _collide_color = 0;
    _mouse_status = 0;
    _x = 0;
    _y = 0;
}

InputEngine  *InputEngine::get() {
    static InputEngine _i;
    return &_i;
}


void InputEngine::init_subsystem() {

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
    unsigned int buttons = SDL_GetMouseState(&_x, &_y);
    if (buttons & SDL_BUTTON(SDL_BUTTON_LEFT)) {
        _mouse_status |= INPUT_LBUTTON;
    } else {
        _mouse_status &= ~INPUT_LBUTTON;
    }
    if (buttons & SDL_BUTTON(SDL_BUTTON_MIDDLE)) {
        _mouse_status |= INPUT_MBUTTON;
    } else {
        _mouse_status &= ~INPUT_MBUTTON;
    }
    if (buttons & SDL_BUTTON(SDL_BUTTON_RIGHT)) {
        _mouse_status |= INPUT_RBUTTON;
    } else {
        _mouse_status &= ~INPUT_RBUTTON;
    }
    _collide_color = VideoEngine::get()->get_collor_at_position(_x, _y);
    if (_mouse_status & INPUT_RBUTTON) {
        DEBUG_MSG("COLOR READED: 0x" << std::hex << _collide_color);
    }
}
