//
// Created by rot on 11/10/16.
//

#ifndef __UONEWCLIENT_PHYSICALCOMPONENT_H
#define __UONEWCLIENT_PHYSICALCOMPONENT_H

#include <cashley/cashley.h>
#include "../common/garbagecollector/texture.h"
#include "../common/garbagecollector/displaylist.h"

#define PC_F_NONE         0x0000
#define PC_F_INTERNAL_DL  0x0001
#define PC_F_DRAG_DELAYED 0x0002
#define PC_F_DISPLAY_FLAT 0x0004


class PhysicalComponentData {
public:
    int x, y, w, h, z;
    unsigned int flags;
    ResourceRef<DisplayList> _dl;
    ResourceRef<Texture> texture;
};

class InputEngine;

class PhysicalComponent : public CAshley::Component {
public:
    void init();
    void shutdown();
//    void setup();
    void setup(int x, int y, int w, int h, int z, ResourceRef<Texture> texture, unsigned int flags = PC_F_NONE);
    void setup(int x, int y, int w, int h, int z, unsigned int flags = PC_F_NONE);
    void setup_with_dl(int x, int y, int z, ResourceRef<DisplayList> dl, unsigned int flags = PC_F_INTERNAL_DL);
    void move(int x, int y, int z);
    void display();
    void reset_status();
    void run();
    unsigned int get_color() { return _color; }
    CASHLEY_COMPONENT
private:
    enum Status {
        BLUR = 0,
        OVER,
        LPUSHED_OVER,
        LPUSHED_BLUR,
        OVER_WAITING,
        LPUSHED2_OVER,
        RPUSHED,
    } _status;
    unsigned int _color;
    ResourceRef<DisplayList> _dl;
    unsigned int _last_action_ticks;
    unsigned int _last_action_ticks_2;
    static unsigned int _color_serial;
    PhysicalComponentData * data;
};

#endif //__UONEWCLIENT_PHYSICALCOMPONENT_H
