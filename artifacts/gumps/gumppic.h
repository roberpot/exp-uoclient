//
// Created by rot on 11/10/16.
//

#ifndef __UONEWCLIENT_GUMPPIC_H
#define __UONEWCLIENT_GUMPPIC_H

#include <cashley/cashley.h>

#include "basegump.h"
#include "../../common/types.h"

class GumpPic : public CAshley::Entity, public BaseGump {
public:
    void init(Form * f, uo_dword gumpid, int x, int y, int z);
    void shutdown();
private:
    uo_dword _gump_id;
};

#endif //__UONEWCLIENT_GUMPPIC_H
