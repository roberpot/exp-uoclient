//
// Created by rot on 13/10/16.
//

#ifndef __UONEWCLIENT_INPUT_H
#define __UONEWCLIENT_INPUT_H


#include "../common/debug.h"


#define INPUT_LBUTTON  0x001
#define INPUT_MBUTTON  0x002
#define INPUT_RBUTTON  0x004
#define INPUT_LCLICK   0x008
#define INPUT_MCLICK   0x010
#define INPUT_RCLICK   0x020
#define INPUT_LRELEASE 0x040
#define INPUT_MRELEASE 0x080
#define INPUT_RRELEASE 0x100


extern class InputEngine {
public:
    InputEngine() {};
    void init_subsystem();
    void halt_subsystem();
    void run();
    inline int get_x() { return _x; }
    inline int get_y() { return _y; }
    inline int get_x_run() { return _x_run; }
    inline int get_y_run() { return _y_run; }
    inline bool lbutton_down() { return bool(_mouse_status & INPUT_LBUTTON); }
    inline bool mbutton_down() { return bool(_mouse_status & INPUT_MBUTTON); }
    inline bool rbutton_down() { return bool(_mouse_status & INPUT_RBUTTON); }
    inline bool lclick() { return bool(_mouse_status & INPUT_LCLICK); }
    inline bool mclick() { return bool(_mouse_status & INPUT_MCLICK); }
    inline bool rclick() { return bool(_mouse_status & INPUT_RCLICK); }
    inline bool lrelease() { return bool(_mouse_status & INPUT_LRELEASE); }
    inline bool mrelease() { return bool(_mouse_status & INPUT_MRELEASE); }
    inline bool rrelease() { return bool(_mouse_status & INPUT_RRELEASE); }
    inline unsigned int get_ticks() { return _ticks_update; }
    inline bool continue_execution() { return _continue_execution; }
    inline unsigned int collide_color() { return _collide_color; }
private:
    InputEngine(const InputEngine &v) { UNREFERENCED_PARAMETER(v); }
    void operator = (const InputEngine &v) { UNREFERENCED_PARAMETER(v); }
    int _x, _y;
    int _x_run, _y_run;
    unsigned short _mouse_status;
    bool _continue_execution;
    unsigned int _collide_color;
    unsigned int _ticks_update;
} input;


#endif //__UONEWCLIENT_INPUT_H
