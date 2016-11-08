//
// Created by rot on 13/10/16.
//

#ifndef __UONEWCLIENT_BASEGUMP_H
#define __UONEWCLIENT_BASEGUMP_H

#include "../artifact.h"
#include "../../common/debug.h"

class Form;

class BaseGump : public Artifact {
public:
    void init(Form * f);
    Form * form();
    virtual void shutdown() {}
    virtual ~BaseGump() { }
protected:
    Form * _form;
    unsigned int _x, _y;
};


#endif //__UONEWCLIENT_BASEGUMP_H
