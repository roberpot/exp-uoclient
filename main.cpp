#include <iostream>

#include <GL/gl.h>
#include <SDL2/SDL.h>

#include "engines/video.h"
#include "resources/gump.h"
#include "resources/font.h"

int main() {
    // Engines.
    VideoEngine * video = VideoEngine::get();
    // Resources.
    GumpManager * gumpmanager = GumpManager::get();
    FontManager * fontmanager = FontManager::get();

    // Initialize systems.
    SDL_Init(0);
    atexit(SDL_Quit);
    video->init_subsystem();
    // Initialize resources.
    gumpmanager->init("gumpidx.mul", "gumpart.mul");
    fontmanager->init("fonts.mul");

    // TODO: remove
    unsigned int text, panete;
    text = fontmanager->rasterize(0, "Cargando...");
    panete = fontmanager->rasterize(3, "Panete es muy muy muy feliz :D :D");

    bool done = false;
    while (!done) {
        // message processing loop
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            // check for messages
            switch (event.type) {
                case SDL_QUIT:
                    done = true;
                    break;
                case SDL_KEYDOWN: {
                    if (event.key.keysym.sym == SDLK_ESCAPE) {
                        done = true;
                    } break;
                }
            } // end switch
        } // end of message processing
        glDisable(GL_TEXTURE_2D);
        //memory->run_physic_components();
        // Process collisions.
        video->clear();
        glEnable(GL_TEXTURE_2D);
        //memory->run_graphic_components();
        glLoadIdentity();
        glDepthMask(GL_FALSE);
        glTranslated(0, 0, 0);
        glCallList(text);
        glTranslated(10, 80, 0);
        glCallList(panete);
        glDepthMask(GL_TRUE);
        glLoadIdentity();
        video->run();
    }

    video->halt_subsystem();
    return 0;
}