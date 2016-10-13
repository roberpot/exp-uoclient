#include <iostream>

#include <GL/gl.h>
#include <SDL2/SDL.h>
#include <cashley/cashley.h>

#include "common/debug.h"
#include "engines/video.h"
#include "engines/input.h"
#include "resources/gump.h"
#include "resources/font.h"
#include "cashley/visualprocessor.h"
#include "contrib/form_login.h"
//#include "cashley/gumppic.h"

int main(int argc, char * argv[]) {
    UNREFERENCED_PARAMETER(argc);
    UNREFERENCED_PARAMETER(argv);
    debug_init();
    // Engines.
    VideoEngine * video = VideoEngine::get();
    InputEngine * input = InputEngine::get();
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
    input->init_subsystem();
    // Initialize resources.
    gumpmanager->init("gumpidx.mul", "gumpart.mul");
    fontmanager->init("fonts.mul");

    // TODO: remove
//    unsigned int text, panete;
//    text = fontmanager->rasterize(0, "Cargando...");
//    panete = fontmanager->rasterize(3, "Panete es muy muy muy feliz :D :D ...");

    Form * loginform = form_login(engine);
    loginform->enable();

    while (input->continue_execution()) {
        input->run();
        video->clear();
//        glLoadIdentity();
//        glDepthMask(GL_FALSE);
//        glTranslated(0, 0, 0);
//        glCallList(text);
//        glTranslated(10, 80, 0);
//        glCallList(panete);
//        glDepthMask(GL_TRUE);
//        glLoadIdentity();
        engine->run_tick(1);
        video->run();
    }
    video->halt_subsystem();
    input->halt_subsystem();
    debug_halt();
    return 0;
}