//
// Created by rot on 11/10/16.
//

#include <queue>
#include <GL/gl.h>

#include "physicalcomponent.h"
#include "visualcomponent.h"
#include "../common/utils.h"
#include "../engines/input.h"
#include "../artifacts/artifact.h"


unsigned int PhysicalComponent::_color_serial = 0xFF000000;

#define MAX_WAIT_FOR_DCLICK  500
#define MAX_WAIT_FOR_DRAG    200


void PhysicalComponent::init() {
    _color = ++_color_serial;
    _dl = ResourceRef<DisplayList>(new DisplayList);
    data = new PhysicalComponentData;
    reset_status();
}

void PhysicalComponent::shutdown() {
    _dl = ResourceRef<DisplayList>();
    delete data;
}

void PhysicalComponent::setup(int x, int y, int w, int h, int z, ResourceRef<Texture> texture, unsigned int flags) {
    data->w = w;
    data->h = h;
    data->texture = texture;
    data->flags = flags;
    move(x, y, z);
}


void PhysicalComponent::setup_with_dl(int x, int y, int z, ResourceRef<DisplayList> dl, unsigned int flags) {
    data->w = 0;
    data->h = 0;
    data->texture = 0;
    data->flags = flags | GC_F_INTERNAL_DL;
    data->_dl = dl;
    move(x, y, z);
}

void PhysicalComponent::move(int x, int y, int z) {
    data->x = x;
    data->y = y;
    data->z = z;
    _dl()->init_compilation();
    if (data->flags & GC_F_INTERNAL_DL) {
        glPushMatrix();
        glTranslated(x, y, data->z);
        data->_dl()->display();
        glPopMatrix();
    } else {
        display_textured_square(x, y, data->w, data->h, data->z, data->texture.get()->get());
    }
    _dl()->end_compilation();
}

void PhysicalComponent::display() {
    _dl()->display();
}

void PhysicalComponent::reset_status() {
    _status = BLUR;
}

void PhysicalComponent::run() {
    // Create event queue.
    enum _EventMessage {
        _BLUR = 0,
        _OVER,
        _LCLICK,
        _MCLICK,
        _RCLICK,
        _LRELEASE,
        _MRELEASE,
        _RRELEASE,
    };
    std::queue<_EventMessage> events;
    if (input.collide_color() == _color) {
        events.push(_OVER);
    } else {
        events.push(_BLUR);
    }
    if (input.lclick()) {
        events.push(_LCLICK);
    }
    if (input.mclick()) {
        events.push(_MCLICK);
    }
    if (input.rclick()) {
        events.push(_RCLICK);
    }
    if (input.lrelease()) {
        events.push(_LRELEASE);
    }
    if (input.mrelease()) {
        events.push(_MRELEASE);
    }
    if (input.rrelease()) {
        events.push(_RRELEASE);
    }
    _EventMessage m;
    while (events.size() > 0) {
        m = events.front();
        switch(_status) {
            case BLUR: {
                switch (m) {
                    case _OVER: {
                        _status = OVER;
                        // call artifact over.
                        DEBUG_INFO("OVER: " << this);
                    }
                    default: break;
                }
            } break;
            case OVER: {
                switch (m) {
                    case _BLUR: {
                        _status = BLUR;
                        // call artifact blur.
                        DEBUG_INFO("BLUR: " << this);
                    } break;
                    case _LCLICK: {
                        _status = LPUSHED_OVER;
                        _last_action_ticks = input.get_ticks();
                    } break;
                    case _RCLICK: {
                        _status = RPUSHED;
                        // call artifact rclick.
                        dynamic_cast<Artifact*>(get_owner())->right_click();
                        DEBUG_INFO("RCLICK: " << this);
                    } break;
                    default: break;
                }
            } break;
            case LPUSHED_OVER: {
                if (!(data->flags & PC_F_DRAG_DELAYED) || (input.get_ticks() - _last_action_ticks > MAX_WAIT_FOR_DRAG)) {
                    // call artifact drag.
                    dynamic_cast<Artifact*>(get_owner())->drag(input.get_x_run(), input.get_y_run());
                    DEBUG_INFO("DRAG: " << this);
                }
                switch(m) {
                    case _BLUR: {
                        _status = LPUSHED_BLUR;
                        // call artifact blur.
                        DEBUG_INFO("BLUR: " << this);
                    } break;
                    case _LRELEASE: {
                        _status = OVER_WAITING;
                    } break;
                    case _RCLICK: {
                        _status = RPUSHED;
                        // call artifact rclick.
                        dynamic_cast<Artifact*>(get_owner())->right_click();
                        DEBUG_INFO("RCLICK: " << this);
                    } break;
                    default: break;
                }
            } break;
            case LPUSHED_BLUR: {
                // call artifact drag.
                dynamic_cast<Artifact*>(get_owner())->drag(input.get_x_run(), input.get_y_run());
                DEBUG_INFO("DRAG: " << this);
                switch(m) {
                    case _LRELEASE: {
                        _status = BLUR;
                    } break;
                    case _OVER: {
                        _status = LPUSHED_OVER;
                        // call artifact over.
                        DEBUG_INFO("OVER: " << this);
                    } break;
                    default: break;
                }
            } break;
            case OVER_WAITING: {
                if (input.get_ticks() > (MAX_WAIT_FOR_DCLICK + _last_action_ticks)) {
                    _status = OVER;
                    // call artifact lclick;
                    DEBUG_INFO("LCLICK: " << this);
                    continue;
                }
                switch(m) {
                    case _RCLICK: {
                        _status = RPUSHED;
                        // call artifact rclick.
                        dynamic_cast<Artifact*>(get_owner())->right_click();
                        DEBUG_INFO("RCLICK: " << this);
                    } break;
                    case _LCLICK: {
                        _status = LPUSHED2_OVER;
                        _last_action_ticks_2 = input.get_ticks();
                    } break;
                    case _BLUR: {
                        _status = BLUR;
                        // call artifact blur.
                        // call artifact lclick.
                        DEBUG_INFO("BLUR: " << this);
                        DEBUG_INFO("LCLICK: " << this);
                    } break;
                    default: break;
                }
            } break;
            case LPUSHED2_OVER: {
                if (input.get_ticks() > (MAX_WAIT_FOR_DCLICK + _last_action_ticks)) {
                    _status = LPUSHED_OVER;
                    _last_action_ticks = _last_action_ticks_2;
                    continue;
                }
                switch(m) {
                    case _RCLICK: {
                        _status = RPUSHED;
                        // call artifact rclick.
                        dynamic_cast<Artifact*>(get_owner())->right_click();
                        DEBUG_INFO("RCLICK: " << this);
                    } break;
                    case _BLUR: {
                        _status = LPUSHED_BLUR;
                        // call artifact blur.
                        DEBUG_INFO("BLUR: " << this);
                    } break;
                    case _LRELEASE: {
                        _status = OVER;
                        if (input.get_ticks() < (MAX_WAIT_FOR_DCLICK + _last_action_ticks)) {
                            // call artifact dlclick.
                            DEBUG_INFO("DLCLICK: " << this);
                        } else {
                            // call artifact lclick.
                            DEBUG_INFO("LCLICK: " << this);
                        }
                    } break;
                    default: break;
                }
            } break;
            case RPUSHED: {
                switch(m) {
                    case _RRELEASE: {
                        if (input.collide_color() == _color) {
                            _status = OVER;
                        } else {
                            _status = BLUR;
                        }
                    } break;
                    default: break;
                }
            } break;
            default: break;
        }
        events.pop();
    }
}