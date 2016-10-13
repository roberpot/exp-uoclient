//
// Created by rot on 12/10/2016.
//

#ifndef __UONEWCLIENT_FORM_H
#define __UONEWCLIENT_FORM_H

#include <vector>

#include <cashley/cashley.h>

#include "gumps/gumps.h"

class Form {
public:
    Form(CAshley::Engine * engine);
    void addgump(BaseGump * g);
    void enable();
    void disable();
private:
    std::vector<BaseGump *> _gumps;
    CAshley::Engine * _engine;
};

#endif //UONEWCLIENT_FORM_H
