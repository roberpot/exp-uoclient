//
// Created by rot on 11/10/16.
//

#ifndef __UONEWCLIENT_GUMPPIC_H
#define __UONEWCLIENT_GUMPPIC_H

#include <cashley/cashley.h>

#include "basegump.h"
#include "../../common/types.h"
#include "../../resources/gump.h"

class GumpPic : public CAshley::Entity, public BaseGump {
public:
    void init(Form * f, uo_dword gumpid, unsigned int x, unsigned int y);
    void move(int x, int y, int z);
    void drag(int x, int y);
    void right_click();
    void shutdown();
    CASHLEY_ENTITY
private:
    ResourceRef<GumpInfo> _gumpref;
};

#endif //__UONEWCLIENT_GUMPPIC_H
