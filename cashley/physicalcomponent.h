//
// Created by rot on 11/10/16.
//

#ifndef __UONEWCLIENT_PHYSICALCOMPONENT_H
#define __UONEWCLIENT_PHYSICALCOMPONENT_H

#include <cashley/cashley.h>


class PhysicalComponent : public CAshley::Component {
public:
    void init();
    void shutdown();
    void setup();
    void display();
    void run();
    CASHLEY_COMPONENT
private:
    unsigned int _color;
    unsigned int _displaylist;
    static unsigned int _color_serial;
};

#endif //__UONEWCLIENT_PHYSICALCOMPONENT_H
