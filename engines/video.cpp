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
            800,                               // width, in pixels
            600,                               // height, in pixels
            SDL_WINDOW_OPENGL                  // flags - see below
    );

    if (!window) {
        DEBUG_ERROR("Unable to set 800x600 video: " << SDL_GetError());
        throw 1;
    }

    // Initialize GL.
    glcontext = SDL_GL_CreateContext(window);

    glClearColor(1,1,1,1);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glClearDepth(1.0f);                   // Set background depth to farthest
    glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling
    glDepthFunc(GL_LEQUAL);    // Set the type of depth-test
    glShadeModel(GL_SMOOTH);   // Enable smooth shading
    //glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections
    glViewport (0 , 0 , 800, 600 ) ;
    glMatrixMode ( GL_PROJECTION ) ;
    glLoadIdentity ();
    glOrtho ( 0,800,600 , 0, 100000, -100000 ) ;
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    next_collide_color = 0;
}

void VideoEngine::halt_subsystem() {
    SDL_GL_DeleteContext(glcontext);
    SDL_DestroyWindow(window);
}

void VideoEngine::run() {
    SDL_GL_SwapWindow(window);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
}

void VideoEngine::clear() {
    glReadPixels(10, 10, 1, 1, GL_RGBA, GL_UNSIGNED_INT_8_8_8_8, &collide_color);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
}

unsigned int VideoEngine::gen_collide_color() {
    unsigned int ret = next_collide_color++;
    return (ret << 8) & 0xFFFFFF00;
}

unsigned int VideoEngine::get_collide_color() {
    return collide_color;
}
