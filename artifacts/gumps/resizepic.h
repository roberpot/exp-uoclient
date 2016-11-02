//
// Created by rot on 17/10/2016.
//

#ifndef __UONEWCLIENT_RESIZEPIC_H
#define __UONEWCLIENT_RESIZEPIC_H

#include <cashley/cashley.h>

#include "basegump.h"
#include "../../common/types.h"
#include "../../common/garbagecollector/texture.h"
#include "../../resources/gump.h"
#include "../../common/garbagecollector/displaylist.h"


class ResizePic : public CAshley::Entity, public BaseGump {
public:
    void init(Form * f, uo_dword gumpid, unsigned int x, unsigned int y, int w, int h);
    void move(int x, int y, int z);
    void drag(int x, int y);
    void right_click();
    void shutdown();
    CASHLEY_ENTITY
private:
    void _prerender(int w, int h, unsigned int color=0);
    ResourceRef<GumpInfo> _ginforefs[9];
    ResourceRef<Texture> _flattextures[9];
    ResourceRef<DisplayList> _dl, _dl2;
};

#endif //__UONEWCLIENT_RESIZEPIC_H
