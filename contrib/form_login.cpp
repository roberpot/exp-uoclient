//
// Created by rot on 13/10/16.
//

#include "form_login.h"
#include "../common/types.h"


Form * form_login(CAshley::Engine * e) {
    Form * f = new Form(e);
    GumpPic * gumpic = new GumpPic;
    gumpic->init(f, 9001, 0, 0);
    ResizePic * resizepic = new ResizePic;
    resizepic->init(f, 5054, 130, 289, 451, 157);
    Text * text = new Text;
    text->init(f, 2, "Log in to Ultima Online", 255, 311);
//    resizepic->init(f, 9350, 130, 289, 60, 40);
//    = new ResizePic;
//    gumpic = new GumpPic;
//    gumpic->init(f, 6, 50, 50, 8);
//    gumpic = new GumpPic;
//    gumpic->init(f, 12, 150, 150, 7);
    return f;
}