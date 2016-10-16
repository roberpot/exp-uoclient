//
// Created by rot on 11/10/16.
//

#include <GL/gl.h>

#include "physicalcomponent.h"
#include "visualcomponent.h"
#include "../common/utils.h"
#include "../engines/input.h"


unsigned int PhysicalComponent::_color_serial = 0;


void PhysicalComponent::init() {
    _color = ++_color_serial;
    _displaylist = glGenLists(1);
    data = new PhysicalComponentData;
}

void PhysicalComponent::shutdown() {
    glDeleteLists(_displaylist, 1);
    delete data;
}

void PhysicalComponent::setup() {
    glNewList(_displaylist, GL_COMPILE);
    glColor4bv((GLbyte*)&_color);
    this->get_owner()->get_component<VisualComponent>()->display();
    glEndList();
}

void PhysicalComponent::setup(int x, int y, int w, int h, int z, unsigned int texture) {
    data->w = w;
    data->h = h;
    data->texture = texture;
    move(x, y, z);
}

void PhysicalComponent::move(int x, int y, int z) {
    data->x = x;
    data->y = y;
    data->z = z;
    glDeleteLists(_displaylist, 1);
    glNewList(_displaylist, GL_COMPILE);
//    if (data->flags & GC_F_INTERNAL_DL) {
//        glPushMatrix0000();
//        glTranslated(x, y, data->z);
//        glCallList(data->internal_dl);
//        glPopMatrix();
//    } else {
        display_textured_square(x, y, data->w, data->h, data->z, data->texture);
//    }
    glEndList();
}

void PhysicalComponent::display() {
    glCallList(_displaylist);
//    this->get_owner()->get_component<VisualComponent>()->display();
}

void PhysicalComponent::run(InputEngine * input) {
    if (input->collide_color() == _color && input->lbutton_down()) {
        DEBUG_MSG("CLICK EN " << this << " X: " << input->get_x() << " Y: " << input->get_y() << " COLOR: " << _color << " INPUT COLOR: " << input->collide_color());
    }
}