//
// Created by rot on 31/10/16.
//

#include "displaylist.h"


DisplayList::DisplayList() {
    _dl = glGenLists(1);
}

DisplayList::~DisplayList() {
    glDeleteLists(_dl, 1);
}

void DisplayList::init_compilation() {
    glDeleteLists(_dl, 1);
    glNewList(_dl, GL_COMPILE);
}

void DisplayList::end_compilation() {
    glEndList();
}
