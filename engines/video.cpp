#include <GL/gl.h>
#ifdef __MINGW32__
#include <GL/glext.h>
#endif

#include "../common/debug.h"
#include "video.h"


VideoEngine  *VideoEngine::get() {
    static VideoEngine _v;
    return &_v;
}

void VideoEngine::init_subsystem() {
    if (SDL_InitSubSystem(SDL_INIT_VIDEO) < 0 ) {
        DEBUG_ERROR("Unable to init SDL: " << SDL_GetError());
        throw 1;
    }
    // create a new window
    window = SDL_CreateWindow(
            "Exp UO Client",                  // window title
            SDL_WINDOWPOS_UNDEFINED,           // initial x position
            SDL_WINDOWPOS_UNDEFINED,           // initial y position
            640,                               // width, in pixels
            480,                               // height, in pixels
            SDL_WINDOW_OPENGL                  // flags - see below
    );

    if (!window) {
        DEBUG_ERROR("Unable to set 800x600 video: " << SDL_GetError());
        throw 1;
    }

    // Initialize GL.
    glcontext = SDL_GL_CreateContext(window);

    glClearColor(0,0,0,0);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glEnable(GL_TEXTURE_2D);
    glClearDepth(1.0f);                   // Set background depth to farthest
    glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling
    glDepthFunc(GL_LEQUAL);    // Set the type of depth-test
    glShadeModel(GL_SMOOTH);   // Enable smooth shading
//    glEnable(GL_BLEND);
//    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_LIGHTING);
//    glEnable(GL_ALPHA_TEST);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections
    glViewport (0 , 0 , 640, 480 ) ;
    glMatrixMode ( GL_PROJECTION ) ;
    glLoadIdentity ();
    glOrtho ( 0,640,480 , 0, 100000, -100000 ) ;
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    next_collide_color = 0;
}

void VideoEngine::halt_subsystem() {
    SDL_GL_DeleteContext(glcontext);
    SDL_DestroyWindow(window);
}

void VideoEngine::run() {

    glEnable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);
    SDL_GL_SwapWindow(window);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
}

void VideoEngine::clear() {
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glColor4f(1.0, 0.0, 0.0, 1.0);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
//    glDepthMask(GL_FALSE);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//    glBlendEquation(GL_FUNC_ADD);
    //glBlendFunc(GL_DST_ALPHA, GL_ZERO);
}

unsigned int VideoEngine::gen_collide_color() {
    unsigned int ret = next_collide_color++;
    return (ret << 8) & 0xFFFFFF00;
}

unsigned int VideoEngine::get_collor_at_position(int x, int y) {
    unsigned int color;
    glReadPixels(x, y, 1, 1, GL_RGBA, GL_UNSIGNED_INT_8_8_8_8, &color);
    return color;
}
