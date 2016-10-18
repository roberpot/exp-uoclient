//
// Created by rot on 17/10/2016.
//

#ifndef __UONEWCLIENT_RESIZEPIC_H
#define __UONEWCLIENT_RESIZEPIC_H

#include <cashley/cashley.h>

#include "basegump.h"
#include "../../common/types.h"
#include "../../resources/gump.h"


class ResizePic : public CAshley::Entity, public BaseGump {
public:
    void init(Form * f, uo_dword gumpid, int x, int y, int z, int w, int h);
    void shutdown();
private:
    void _prerender(GumpInfo * ginfo, int w, int h);
    uo_dword _gump_id;
    GumpInfo _ginfo[9], _ginfoflat[9];
    unsigned int _dl, _dl2;
};

#endif //__UONEWCLIENT_RESIZEPIC_H
