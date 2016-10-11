#include <iostream>

#include <GL/gl.h>
#include <SDL2/SDL.h>
#include <cashley/cashley.h>

#include "common/debug.h"
#include "engines/video.h"
#include "resources/gump.h"
#include "resources/font.h"
#include "cashley/visualprocessor.h"
#include "cashley/gumppic.h"

int main() {
    debug_init();
    // Engines.
    VideoEngine * video = VideoEngine::get();
    // Resources.
    GumpManager * gumpmanager = GumpManager::get();
    FontManager * fontmanager = FontManager::get();
    CAshley::Engine * engine = new CAshley::Engine;
    engine->add_processor<VisualProcessor>();
    engine->get_processor<VisualProcessor>()->activate();

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

    GumpPic * entity = new GumpPic;
    engine->add_entity(entity);
    entity->init(6, 50, 50, 0);
    entity->activate();

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
        engine->run_tick(1);
        video->run();
    }
    video->halt_subsystem();
    debug_halt();
    return 0;
}