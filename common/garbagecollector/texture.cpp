//
// Created by rot on 28/10/16.
//

#include <GL/gl.h>
#ifdef __MINGW32__
#include <GL/glext.h>
#endif

#include "texture.h"
#include "../debug.h"

Texture::Texture(SDL_Surface * surface) {
    glGenTextures(1, &_t);
    glBindTexture(GL_TEXTURE_2D, _t);
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB,
                  surface->w, surface->h, 0, GL_BGR,
                  GL_UNSIGNED_BYTE, surface->pixels);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

Texture::Texture(unsigned int width, unsigned int height, void * rawpixels) {
    glGenTextures(1, &_t);
    glBindTexture(GL_TEXTURE_2D, _t);
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA,
                  width, height, 0, GL_RGBA,
                  GL_UNSIGNED_BYTE, rawpixels);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    GLenum err;
    if ((err = glGetError()) != GL_NO_ERROR) {
        DEBUG_ERROR("OpenGL Error" << err);
    }
}

void Texture::apply() {
    glBindTexture(GL_TEXTURE_2D, _t);
}

Texture::~Texture() {
    glDeleteTextures(1, &_t);
}