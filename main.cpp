#include <iostream>

#include <SDL2/SDL.h>
#include <cashley/cashley.h>

#include "engines/video.h"
#include "engines/input.h"
#include "resources/gump.h"
#include "resources/font.h"
#include "resources/hues.h"
#include "cashley/inputprocessor.h"
#include "cashley/physicsprocessor.h"
#include "cashley/visualprocessor.h"
#include "contrib/form_login.h"
#include "common/debug.h"


int main(int argc, char * argv[]) {
    UNUSED_PARAMETER(argc);
    UNUSED_PARAMETER(argv);
    debug_init();

    // Initialize systems.
    SDL_Init(0);
    atexit(SDL_Quit);
    video.init_subsystem();
    input.init_subsystem();
    // Initialize resources.
    gumpmanager.init("gumpidx.mul", "gumpart.mul");
    fontmanager.init("fonts.mul");
    huesmanager.init("hues.mul");

    // Initialize cashley engine.
    CAshley::Engine * engine = new CAshley::Engine;
    engine->add_processor<PhysicsProcessor>(0);
    engine->get_processor<PhysicsProcessor>()->activate();
    engine->add_processor<InputProcessor>(1);
    engine->get_processor<InputProcessor>()->activate();
    engine->add_processor<VisualProcessor>(2);
    engine->get_processor<VisualProcessor>()->activate();
    Form * f1 = form_login(engine);
    Form * f2 = form_login(engine);
//    Form * f3 = form_login(engine);
    f1->enable();
    f2->enable();
//    f3->enable();
    unsigned int ticks_init, ticks_end;

    while (input.continue_execution()) {
        ticks_init = SDL_GetTicks();
        engine->run_tick(1);
        ticks_end = SDL_GetTicks();
        SDL_Delay(MAX(50 + ticks_init, ticks_end) - ticks_end);
    }
    f1->disable();
    f2->disable();
    delete f1;
    delete f2;
    delete engine;
    gumpmanager.halt();
    fontmanager.halt();
    video.halt_subsystem();
    input.halt_subsystem();
    debug_halt();
    return 0;
}