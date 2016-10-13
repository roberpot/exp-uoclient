//
// Created by rot on 11/10/16.
//

#ifndef __UONEWCLIENT_VISUALCOMPONENT_H
#define __UONEWCLIENT_VISUALCOMPONENT_H

#include <cashley/cashley.h>

#define GC_F_NONE         0x0000
#define GC_F_INTERNAL_DL  0x0001

class VisualComponentData {
public:
    int x, y, w, h, z;
    unsigned int texture, flags;
    unsigned int internal_dl;
};

class VisualComponent : public CAshley::Component {
public:
    void init();
    void setup(int x, int y, int w, int h, int z, unsigned int texture, unsigned int flags = GC_F_NONE);
    void setup_with_dl(int x, int y, int z, unsigned int dl, unsigned int flags = GC_F_INTERNAL_DL);
    void move(int x, int y, int z);
    void shutdown();
    void display();
    CASHLEY_COMPONENT
private:
    unsigned int _displaylist;
    VisualComponentData * data;
};

#endif //__UONEWCLIENT_VISUALCOMPONENT_H
