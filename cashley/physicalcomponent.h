//
// Created by rot on 11/10/16.
//

#ifndef __UONEWCLIENT_PHYSICALCOMPONENT_H
#define __UONEWCLIENT_PHYSICALCOMPONENT_H

#include <cashley/cashley.h>

class PhysicalComponentData {
public:
    int x, y, w, h, z;
    unsigned int texture, flags;
    unsigned int internal_dl;
};

class InputEngine;

class PhysicalComponent : public CAshley::Component {
public:
    void init();
    void shutdown();
    void setup();
    void setup(int x, int y, int w, int h, int z, unsigned int texture);
    void move(int x, int y, int z);
    void display();
    void run(InputEngine * input);
    unsigned int get_color() { return _color; }
    CASHLEY_COMPONENT
private:
    unsigned int _color;
    unsigned int _displaylist;
    static unsigned int _color_serial;
    PhysicalComponentData * data;
};

#endif //__UONEWCLIENT_PHYSICALCOMPONENT_H
