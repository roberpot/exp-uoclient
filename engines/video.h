//
// Created by rot on 10/10/16.
//

#ifndef __UONEWCLIENT_VIDEO_H
#define __UONEWCLIENT_VIDEO_H

#include <SDL2/SDL.h>

#include "../common/debug.h"
#include "../shaders/textureloader.h"

class VideoEngine {
public:
    static VideoEngine * get();
    void init_subsystem();
    void halt_subsystem();
    void run();
    void clear();
    void force_flush();
    unsigned int get_collor_at_position(int x, int y);
    inline int get_program_object() { return _programobject; }
private:
    VideoEngine() {}
    VideoEngine(const VideoEngine &v) { UNREFERENCED_PARAMETER(v); }
    void operator = (const VideoEngine &v) { UNREFERENCED_PARAMETER(v); }
    void compile_shaders();
    static VideoEngine _v;
    unsigned int w, h;

    SDL_Window * window;
    SDL_GLContext glcontext;

    unsigned int _programobject;
    unsigned int _texture_fragment_shader, _texture_vertex_shader;
};

#endif //__UONEWCLIENT_VIDEO_H
