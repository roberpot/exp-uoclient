//
// Created by rot on 13/10/16.
//

#include "../form.h"
#include "basegump.h"


void BaseGump::init(Form * f) {
    _form = f;
    _form->addgump(this);
}

Form * BaseGump::form() {
    return _form;
}
