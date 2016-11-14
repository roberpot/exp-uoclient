//
// Created by rot on 14/11/16.
//

#ifndef __UONEWCLIENT_KEY_H
#define __UONEWCLIENT_KEY_H

#include <SDL2/SDL.h>

class Key { // SDL_GetModState
public:
    Key(SDL_Keycode _k);
    Key(const Key & k);
    Key operator=(Key k);
    operator char();
private:
    SDL_Keycode _key;
    bool _ctrl, _alt, _shift;
    char _v;
};

class KeyComp {
public:
    bool operator()(Key a, Key b);
};

class KeyCompMacro {
public:
    bool operator()(Key a, Key b);
};

#endif //__UONEWCLIENT_KEY_H
