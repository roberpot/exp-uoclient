//
// Created by rot on 11/10/16.
//

#include <GL/gl.h>

#include "../common/debug.h"
#include "../common/utils.h"
#include "visualcomponent.h"

void VisualComponent::init() {

}

void VisualComponent::setup(int x, int y, int w, int h, int z, unsigned int texture, unsigned int flags) {
    UNREFERENCED_PARAMETER(flags);
    displaylist_id = glGenLists(1);
    glNewList(displaylist_id, GL_COMPILE);
    display_textured_square(x, y, w, h, z, texture);
    glEndList();
}

void VisualComponent::shutdown() {
//    if (settings->flags & GC_F_DELETE_DL) {
//        glDeleteLists(displaylist_id, 1);
//    }
}

void VisualComponent::display() {
    glCallList(displaylist_id);
}