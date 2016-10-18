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
    gumpic->init(f, 9002, 0, 0, 10);
    ResizePic * resizepic = new ResizePic;
    resizepic->init(f, 2600, 50, 50, 9, 400, 400);
    gumpic = new GumpPic;
    gumpic->init(f, 6, 50, 50, 8);
    gumpic = new GumpPic;
    gumpic->init(f, 12, 150, 150, 7);
    Text * text = new Text;
    text->init(f, 0, "25 de diciembre XuN XuN XuN", 10, 10, 6);
    text = new Text;
    text->init(f, 0, "25 de diciembre XuN XuN XuN !!!!", 40, 400, 5);
    return f;
}