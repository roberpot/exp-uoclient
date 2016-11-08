//
// Created by rot on 11/10/16.
//

#include <GL/gl.h>

#include "../common/debug.h"
#include "../common/utils.h"
#include "visualcomponent.h"

void VisualComponent::init() {
    data = new VisualComponentData;
    _dl = ResourceRef<DisplayList>(new DisplayList);
}


void VisualComponent::setup_with_dl(int x, int y, int z, ResourceRef<DisplayList> dl, unsigned int flags) {
    data->w = 0;
    data->h = 0;
    data->texture = 0;
    data->flags = flags;
    data->_dl = dl;
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
    _dl()->init_compilation();
    if (data->flags & GC_F_INTERNAL_DL) {
        glPushMatrix();
        glTranslated(x, y, z);
        data->_dl()->display();
        glPopMatrix();
    } else {
        display_textured_square(x, y, data->w, data->h, z, data->texture.get()->get());
    }
    _dl()->end_compilation();
}

void VisualComponent::shutdown() {
    _dl = ResourceRef<DisplayList>();
    if (data) {
        delete data;
        data = 0;
    }
}

void VisualComponent::display() {
    _dl()->display();
}