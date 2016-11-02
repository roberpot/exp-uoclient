//
// Created by rot on 12/10/2016.
//

#ifndef __UONEWCLIENT_FORM_H
#define __UONEWCLIENT_FORM_H

#include <vector>

#include <cashley/cashley.h>

#include "gumps/gumps.h"

#define FORM_FLAG_NOMOVE  0x01
#define FORM_FLAG_NOCLOSE 0x02

class Form {
public:
    Form(CAshley::Engine * engine, uo_char flags=0);
    ~Form();
    void addgump(BaseGump * g);
    void enable();
    void disable();
    void close();
    void move(int x, int y);
private:
    uo_char _flags;
    unsigned int _uid;
    unsigned int _x, _y, _z;
    std::vector<BaseGump *> _gumps;
    CAshley::Engine * _engine;
};

#endif //UONEWCLIENT_FORM_H
