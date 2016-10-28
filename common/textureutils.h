//
// Created by rot on 10/10/16.
//

#ifndef __UONEWCLIENT_TEXTUREUTILS_H
#define __UONEWCLIENT_TEXTUREUTILS_H

#include <SDL2/SDL.h>

unsigned int generate_texture_from_surface(SDL_Surface * surface);
unsigned int generate_texture_from_rawwew(unsigned int width, unsigned int height, void * rawpixels);
void remove_texture(unsigned int i);

#endif //__UONEWCLIENT_TEXTUREUTILS_H
