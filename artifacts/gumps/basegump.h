//
// Created by rot on 13/10/16.
//

#ifndef __UONEWCLIENT_BASEGUMP_H
#define __UONEWCLIENT_BASEGUMP_H

#include "../artifact.h"

class Form;

class BaseGump : public Artifact {
public:
    void init(Form * f);
    Form * form();
protected:
    Form * _form;
};


#endif //__UONEWCLIENT_BASEGUMP_H
