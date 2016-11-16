//
// Created by rot on 16/11/16.
//

#ifndef __UONEWCLIENT_BUTTON_H
#define __UONEWCLIENT_BUTTON_H

#include <cashley/cashley.h>

#include "basegump.h"
#include "../../common/types.h"
#include "../../resources/gump.h"


class Button : public CAshley::Entity, public BaseGump {
public:
    void init(Form * f, uo_dword gumpid, uo_dword gumpover, uo_dword gumpin, unsigned int x, unsigned int y);
    void move(int x, int y, int z);
    void shutdown();
    ~Button() {}
    CASHLEY_ENTITY
private:
    ResourceRef<GumpInfo> _gumpref, _gumprefover, _gumprefin;
    ResourceRef<Texture> _p_texref, _p_texrefover, _p_texrefin;
    unsigned int _color;
};

#endif //__UONEWCLIENT_BUTTON_H
