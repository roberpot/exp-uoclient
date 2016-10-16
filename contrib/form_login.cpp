//
// Created by rot on 13/10/16.
//

#include "form_login.h"
#include "../artifacts/gumps/gumps.h"
#include "../common/types.h"


Form * form_login(CAshley::Engine * e) {
    Form * f = new Form(e);
    GumpPic * gumpic = new GumpPic;
    gumpic->init(f, 9002, 0, 0, 0);
    gumpic = new GumpPic;
    gumpic->init(f, 6, 50, 50, 0);
    gumpic = new GumpPic;
    gumpic->init(f, 12, 150, 150, 0);
    Text * text = new Text;
    text->init(f, 0, "JAJAJA", 10, 10, 0);
    return f;
}