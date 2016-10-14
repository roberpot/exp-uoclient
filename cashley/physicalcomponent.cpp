//
// Created by rot on 11/10/16.
//

#include <GL/gl.h>

#include "physicalcomponent.h"
#include "visualcomponent.h"


unsigned int PhysicalComponent::_color_serial = 0;


void PhysicalComponent::init() {
    _color = ++_color_serial;
    _displaylist = glGenLists(1);
}

void PhysicalComponent::shutdown() {
    glDeleteLists(_displaylist, 1);
}

void PhysicalComponent::setup() {
    glNewList(_displaylist, GL_COMPILE);
    glColor4bv((GLbyte*)&_color);
    this->get_owner()->get_component<VisualComponent>()->display();
    glEndList();
}

void PhysicalComponent::display() {
    if (!glIsList(_displaylist)) {
        throw 1;
    }
    glCallList(_displaylist);
//    this->get_owner()->get_component<VisualComponent>()->display();
}

void PhysicalComponent::run() {

}