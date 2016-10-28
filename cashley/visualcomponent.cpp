//
// Created by rot on 11/10/16.
//

#include <GL/gl.h>

#include "../common/debug.h"
#include "../common/utils.h"
#include "visualcomponent.h"

void VisualComponent::init() {
    data = new VisualComponentData;
    _displaylist = glGenLists(1);
}


void VisualComponent::setup_with_dl(int x, int y, int z, unsigned int dl, unsigned int flags) {
    data->w = 0;
    data->h = 0;
    data->texture = 0;
    data->flags = flags;
    data->internal_dl = dl;
    move(x, y, z);
}

void VisualComponent::setup(int x, int y, int w, int h, int z, ResourceRef<Texture> texture, unsigned int flags) {
    data->w = w;
    data->h = h;
    data->texture = texture;
    data->flags = flags;
    move(x, y, z);
}

void VisualComponent::move(int x, int y, int z) {
    data->x = x;
    data->y = y;
    data->z = z;
    glDeleteLists(_displaylist, 1);
    glNewList(_displaylist, GL_COMPILE);
    if (data->flags & GC_F_INTERNAL_DL) {
        glPushMatrix();
        glTranslated(x, y, z);
        glCallList(data->internal_dl);
        glPopMatrix();
    } else {
        display_textured_square(x, y, data->w, data->h, z, data->texture.get()->get());
    }
    glEndList();
}

void VisualComponent::shutdown() {
    glDeleteLists(_displaylist, 1);
    delete data;
}

void VisualComponent::display() {
    glCallList(_displaylist);
}