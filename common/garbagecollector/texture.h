//
// Created by rot on 28/10/16.
//

#ifndef __UONEWCLIENT_TEXTURE_H
#define __UONEWCLIENT_TEXTURE_H

#include "resourcereferencer.h"

#include <SDL2/SDL.h>


class Texture : public AutoRemovedResource {
public:
    Texture(SDL_Surface * surface);
    Texture(unsigned int width, unsigned int height, void * rawpixels);
    void apply();
    inline unsigned int get() { return _t; }
    ~Texture();
private:
    unsigned int _t;
};

#endif //__UONEWCLIENT_TEXTURE_H
