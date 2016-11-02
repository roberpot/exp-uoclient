
#include <cstring>

#include <GL/glew.h>
#include <GL/gl.h>
#ifdef __MINGW32__
#include <GL/glext.h>
#endif

#include "../common/debug.h"
#include "video.h"


void VideoEngine::init_subsystem() {
    if (SDL_InitSubSystem(SDL_INIT_VIDEO) < 0 ) {
        DEBUG_ERROR("Unable to init SDL: " << SDL_GetError());
        throw 1;
    }
    w = 640;
    h = 480;
    // create a new window
    DEBUG_INFO("Initialize window...");
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
    DEBUG_INFO("Initialize window... OK");
    DEBUG_INFO("Initialize GL context...");
    // Initialize GL.
    glcontext = SDL_GL_CreateContext(window);
    glClearColor(1, 1, 1, 0);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glEnable(GL_TEXTURE_2D);
    glClearDepth(1.0f);      // Set background depth to farthest
    glEnable(GL_DEPTH_TEST); // Enable depth testing for z-culling
    glDepthFunc(GL_LEQUAL);  // Set the type of depth-test
    glShadeModel(GL_SMOOTH); // Enable smooth shading
    glDisable(GL_LIGHTING);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections
    glViewport (0 , 0 , w, h ) ;
    glMatrixMode ( GL_PROJECTION ) ;
    glLoadIdentity ();
    glOrtho (0, w, h, 0, 100000, -100000 ) ;
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glReadBuffer(GL_BACK);
    DEBUG_INFO("Initialize GL context... OK");
    DEBUG_INFO("Initialize shaders...");
    compile_shaders();
    DEBUG_INFO("Initialize shaders... OK");
}

void VideoEngine::halt_subsystem() {
    SDL_GL_DeleteContext(glcontext);
    SDL_DestroyWindow(window);
}

void VideoEngine::compile_shaders() {
    DEBUG_INFO("Reading texture shader...");
    glewInit();
    _texture_vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    _texture_fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    unsigned int len_vertex = (unsigned int)strlen(TEXTURE_VERTEX_SHADER);
    unsigned int len_fragment = (unsigned int)strlen(TEXTURE_FRAGMENT_SHADER);
    glShaderSourceARB(_texture_vertex_shader, 1, &TEXTURE_VERTEX_SHADER, (const int *)&len_vertex);
    glShaderSourceARB(_texture_fragment_shader, 1, &TEXTURE_FRAGMENT_SHADER, (const int *)&len_fragment);
    DEBUG_INFO("Reading texture shader... OK");
    DEBUG_INFO("Compiling texture shader...");
    glCompileShaderARB(_texture_vertex_shader);
    int compiled;
    glGetObjectParameterivARB(_texture_vertex_shader, GL_COMPILE_STATUS, &compiled);
    if (!compiled) {
        GLint blen = 0;
        GLsizei slen = 0;
        glGetShaderiv(_texture_vertex_shader, GL_INFO_LOG_LENGTH, &blen);
        if (blen > 1)
        {
            GLchar* compiler_log = (GLchar*)malloc((size_t)blen);

            glGetInfoLogARB(_texture_vertex_shader, blen, &slen, compiler_log);
            DEBUG_ERROR("compiler_log: " << compiler_log);
            free (compiler_log);
        }
        throw 1;
    }
    glCompileShaderARB(_texture_fragment_shader);
    glGetObjectParameterivARB(_texture_fragment_shader, GL_COMPILE_STATUS, &compiled);
    if (!compiled) {
        GLint blen = 0;
        GLsizei slen = 0;
        glGetShaderiv(_texture_fragment_shader, GL_INFO_LOG_LENGTH, &blen);
        if (blen > 1)
        {
            GLchar* compiler_log = (GLchar*)malloc((size_t)blen);

            glGetInfoLogARB(_texture_fragment_shader, blen, &slen, compiler_log);
            DEBUG_ERROR("compiler_log: " << compiler_log);
            free (compiler_log);
        }
        throw 1;
    }
    DEBUG_INFO("Compiling texture shader... OK");
    DEBUG_INFO("Linking texture shader...");
    _programobject = glCreateProgram();
    glAttachShader(_programobject, _texture_vertex_shader);
    glAttachShader(_programobject, _texture_fragment_shader);
    glLinkProgram(_programobject);
    int linked;
    glGetProgramiv(_programobject, GL_LINK_STATUS, &linked);
    if (!linked) {
        throw 2;
    }
    DEBUG_INFO("Linking texture fragment shader... OK");
    glUseProgram(_programobject);
}

void VideoEngine::run() {
    SDL_GL_SwapWindow(window);
    clear();
}

void VideoEngine::clear() {
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glColor4f(1.0, 0.0, 0.0, 1.0);
}

unsigned int VideoEngine::get_collor_at_position(int x, int y) {
    unsigned int color;
    color = 0;
    glReadPixels(x, h - y, 1, 1, GL_RGBA, GL_UNSIGNED_INT_8_8_8_8_REV, &color);
    return color;
}
