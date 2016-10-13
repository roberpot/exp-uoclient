//
// Created by rot on 11/10/16.
//

#include "physicalcomponent.h"


unsigned int PhysicalComponent::_color_serial = 0;


void PhysicalComponent::init() {
    _color = ++_color_serial;
}

