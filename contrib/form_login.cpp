//
// Created by rot on 13/10/16.
//

#include "form_login.h"
#include "../common/types.h"


Form * form_login(CAshley::Engine * e) {
    Form * f = new Form(e, FORM_FLAG_NOMOVE | FORM_FLAG_NOCLOSE);
    GumpPic * gumpic = new GumpPic;
    gumpic->init(f, 9001, 0, 0);
    ResizePic * resizepic = new ResizePic;
    resizepic->init(f, 5054, 130, 289, 451, 157);
    Text * text = new Text;
    text->init(f, 2, "Log in to Ultima Online", 255, 309, 1000);
    text = new Text;
    text->init(f, 2, "Account Name", 182, 347, 1000);
    text = new Text;
    text->init(f, 2, "Password", 182, 387, 1000);
    text = new Text;
    text->init(f, 1, "UO Version 0.0.1 (Open Source Client)", 202, 417, 1000);
    text = new Text;
    text->init(f, 1, "https://github.com/roberpot/exp-uoclient", 202, 455, 1000);
    resizepic = new ResizePic;
    resizepic->init(f, 9350, 329, 344, 209, 30);
    resizepic = new ResizePic;
    resizepic->init(f, 9350, 329, 384, 209, 30);
//    = new ResizePic;
//    gumpic = new GumpPic;
//    gumpic->init(f, 6, 50, 50, 8);
//    gumpic = new GumpPic;
//    gumpic->init(f, 12, 150, 150, 7);
    return f;
}