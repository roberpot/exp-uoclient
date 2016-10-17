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
    w = 640;
    h = 480;
    // create a new window
    window = SDL_CreateWindow(
            "Exp UO Client",                  // window title
            SDL_WINDOWPOS_UNDEFINED,           // initial x position
            SDL_WINDOWPOS_UNDEFINED,           // initial y position
            w,                               // width, in pixels
            h,                               // height, in pixels
            SDL_WINDOW_OPENGL                  // flags - see below
    );

    if (!window) {
        DEBUG_ERROR("Unable to set 800x600 video: " << SDL_GetError());
        throw 1;
    }

    // Initialize GL.
    glcontext = SDL_GL_CreateContext(window);
//    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    glClearColor(1, 1, 1, 0);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glEnable(GL_TEXTURE_2D);
    glClearDepth(1.0f);                   // Set background depth to farthest
//    glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling
    glDepthFunc(GL_LEQUAL);    // Set the type of depth-test
    glShadeModel(GL_SMOOTH);   // Enable smooth shading
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections
    glViewport (0 , 0 , w, h ) ;
    glMatrixMode ( GL_PROJECTION ) ;
    glLoadIdentity ();
    glOrtho (0, w, h, 0, 100000, -100000 ) ;
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void VideoEngine::halt_subsystem() {
    SDL_GL_DeleteContext(glcontext);
    SDL_DestroyWindow(window);
}

void VideoEngine::run() {
    SDL_GL_SwapWindow(window);
    clear();
}

void VideoEngine::clear() {
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glColor4f(1.0, 0.0, 0.0, 1.0);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void VideoEngine::force_flush() {
    glFinish();
}

unsigned int VideoEngine::get_collor_at_position(int x, int y) {
    unsigned int color;
    color = 0;
    glReadBuffer(GL_BACK);
    glFinish();
    glReadPixels(x, h - y, 1, 1, GL_RGBA, GL_UNSIGNED_INT_8_8_8_8_REV, &color);
    return color;
}
