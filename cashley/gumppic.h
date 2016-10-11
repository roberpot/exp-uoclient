//
// Created by rot on 11/10/16.
//

#ifndef __UONEWCLIENT_GUMPPIC_H
#define __UONEWCLIENT_GUMPPIC_H

#include <cashley/cashley.h>

class GumpPic : public CAshley::Entity {
public:
    void init(uo_dword gumpid, int x, int y, int z);
    void shutdown();
private:
    uo_dword _gump_id;
};

#endif //__UONEWCLIENT_GUMPPIC_H
