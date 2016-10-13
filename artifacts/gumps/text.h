//
// Created by rot on 13/10/16.
//

#ifndef __UONEWCLIENT_TEXT_H
#define __UONEWCLIENT_TEXT_H

#include <string>

#include <cashley/cashley.h>

#include "basegump.h"
#include "../../common/types.h"

class Text : public CAshley::Entity, public BaseGump {
public:
    void init(Form * f, unsigned int font, const char * t, int x, int y, int z);
    void init(Form * f, unsigned int font, std::string t, int x, int y, int z);
    void shutdown();
private:
    unsigned int _text;
};

#endif //__UONEWCLIENT_TEXT_H
