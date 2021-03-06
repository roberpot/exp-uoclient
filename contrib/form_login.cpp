//
// Created by rot on 13/10/16.
//

#include "form_login.h"


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
    TextEntry * textentry;
    textentry = new TextEntry;
    textentry->init(f, 1, "username", "", 333, 348, 200, 22);
    PasswordEntry * passwordentry = new PasswordEntry;
    passwordentry->init(f, 1, "password", "", 333, 388, 200, 22);  // 0x1589 N O I
    Button * button = new Button;
    button->init(f, 0x1589, 0x158a, 0x158b, 554, 3);
    button = new Button;
    button->init(f, 0x15a4, 0x15a5, 0x15a6, 611, 434);
    return f;
}