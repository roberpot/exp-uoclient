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
    void init(Form * f, uo_dword gumpid, int x, int y, int z);
    void shutdown();
    CASHLEY_ENTITY
private:
    GumpInfoRef _gumpref;
};

#endif //__UONEWCLIENT_GUMPPIC_H
