//
// Created by rot on 13/10/16.
//

#include "form_login.h"
#include "../artifacts/gumps/gumps.h"
#include "../common/types.h"


Form * form_login(CAshley::Engine * e) {
    Form * f = new Form(e);
    GumpPic * gumpic;
    gumpic = new GumpPic;
    gumpic->init(f, 9002, 0, 0, 0);
    ResizePic * resizepic = new ResizePic;
    resizepic->init(f, 2600, 50, 50, 400, 400, 1);
    gumpic = new GumpPic;
    gumpic->init(f, 6, 50, 50, 2);
    gumpic = new GumpPic;
    gumpic->init(f, 12, 150, 150, 3);
    Text * text = new Text;
    text->init(f, 0, "JAJAJA", 10, 10, 4);
    return f;
}