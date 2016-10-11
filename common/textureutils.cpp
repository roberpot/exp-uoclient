//
// Created by rot on 10/10/16.
//

#include <GL/gl.h>

#include "textureutils.h"
//#include "debug.h"

unsigned int generate_texture_from_surface(SDL_Surface * surface)
{
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB,
                  surface->w, surface->h, 0, GL_BGR,
                  GL_UNSIGNED_BYTE, surface->pixels);
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    return texture;
}

unsigned int generate_texture_from_raw(unsigned int width, unsigned int height, void * rawpixels)
{
    unsigned int texture;

    glEnable(GL_TEXTURE_2D);
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA,
                  width, height, 0, GL_RGBA,
                  GL_UNSIGNED_BYTE, rawpixels);
    GLenum err;
    if ((err = glGetError()) != GL_NO_ERROR) {
        //DEBUG_MSG("OpenGL Error" << err);
    } else {
        //DEBUG_MSG("New texture " << texture);
    }

    return texture;
}

void remove_texture(unsigned int i) {
    glDeleteTextures(1, &i);
}
