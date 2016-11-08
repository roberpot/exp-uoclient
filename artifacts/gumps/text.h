//
// Created by rot on 13/10/16.
//

#ifndef __UONEWCLIENT_TEXT_H
#define __UONEWCLIENT_TEXT_H

#include <string>

#include <cashley/cashley.h>

#include "basegump.h"
#include "../../common/types.h"
#include "../../common/garbagecollector/displaylist.h"

class Text : public CAshley::Entity, public BaseGump {
public:
    void init(Form * f, unsigned int font, const char * t, unsigned int x, unsigned int y);
    void init(Form * f, unsigned int font, std::string t, unsigned int x, unsigned int y);
    void move(int x, int y, int z);
    void shutdown();
    ~Text() {}
private:
    ResourceRef<DisplayList> _text;
};

#endif //__UONEWCLIENT_TEXT_H
