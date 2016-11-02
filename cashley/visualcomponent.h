//
// Created by rot on 11/10/16.
//

#ifndef __UONEWCLIENT_VISUALCOMPONENT_H
#define __UONEWCLIENT_VISUALCOMPONENT_H

#include <cashley/cashley.h>
#include "../common/garbagecollector/texture.h"
#include "../common/garbagecollector/displaylist.h"

#define GC_F_NONE         0x0000
#define GC_F_INTERNAL_DL  0x0001

class VisualComponentData {
public:
    int x, y, w, h, z;
    unsigned int flags;
    ResourceRef<DisplayList> _dl;
    ResourceRef<Texture> texture;
};

class VisualComponent : public CAshley::Component {
public:
    void init();
    void setup(int x, int y, int w, int h, int z, ResourceRef<Texture> texture, unsigned int flags = GC_F_NONE);
    void setup_with_dl(int x, int y, int z, ResourceRef<DisplayList> dl, unsigned int flags = GC_F_INTERNAL_DL);
    void move(int x, int y, int z);
    void shutdown();
    void display();
    CASHLEY_COMPONENT
private:
    ResourceRef<DisplayList> _dl;
    VisualComponentData * data;
};

#endif //__UONEWCLIENT_VISUALCOMPONENT_H
