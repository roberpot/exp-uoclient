//
// Created by rot on 10/10/16.
//

#ifndef __UONEWCLIENT_VIDEO_H
#define __UONEWCLIENT_VIDEO_H

#include <SDL2/SDL.h>

#include "../common/debug.h"

class VideoEngine {
public:
    static VideoEngine * get();
    void init_subsystem();
    void halt_subsystem();
    void run();
    void clear();
    void prepare_for_graphics();
    void prepare_for_physics();
    unsigned int gen_collide_color();
    unsigned int get_collor_at_position(int x, int y);
private:
    VideoEngine() {}
    VideoEngine(const VideoEngine &v) { UNREFERENCED_PARAMETER(v); }
    void operator = (const VideoEngine &v) { UNREFERENCED_PARAMETER(v); }
    static VideoEngine _v;

    SDL_Window * window;
    SDL_GLContext glcontext;
    unsigned int next_collide_color;
};

#endif //__UONEWCLIENT_VIDEO_H
