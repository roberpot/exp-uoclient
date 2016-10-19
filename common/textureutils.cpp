//
// Created by rot on 10/10/16.
//

#include <GL/gl.h>
#ifdef __MINGW32__
#include <GL/glext.h>
#endif

#include "debug.h"
#include "textureutils.h"


unsigned int generate_texture_from_surface(SDL_Surface * surface)
{
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB,
                  surface->w, surface->h, 0, GL_BGR,
                  GL_UNSIGNED_BYTE, surface->pixels);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    return texture;
}

unsigned int generate_texture_from_raw(unsigned int width, unsigned int height, void * rawpixels)
{
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA,
                  width, height, 0, GL_RGBA,
                  GL_UNSIGNED_BYTE, rawpixels);
    GLenum err;
    if ((err = glGetError()) != GL_NO_ERROR) {
        DEBUG_ERROR("OpenGL Error" << err);
    } else {
        DEBUG_MSG("New texture " << texture);
    }
    return texture;
}

void remove_texture(unsigned int i) {
    glDeleteTextures(1, &i);
}
