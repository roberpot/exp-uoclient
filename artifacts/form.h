//
// Created by rot on 12/10/2016.
//

#ifndef __UONEWCLIENT_FORM_H
#define __UONEWCLIENT_FORM_H

#include <cashley/cashley.h>

class Form {
public:
    Form(CAshley::Engine * engine);
    void enable();
    void disable();
private:
    CAshley::Entity ** _entities;
    CAshley::Engine * _engine;
};

#endif //UONEWCLIENT_FORM_H
