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


class InputEngine {
public:
    static InputEngine * get();
    void init_subsystem();
    void halt_subsystem();
    void run();
    inline int get_x() { return _x; }
    inline int get_y() { return _y; }
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
    InputEngine();
    InputEngine(const InputEngine &v) { UNREFERENCED_PARAMETER(v); }
    void operator = (const InputEngine &v) { UNREFERENCED_PARAMETER(v); }
    static InputEngine _i;
    int _x, _y;
    unsigned short _mouse_status;
    bool _continue_execution;
    unsigned int _collide_color;
    unsigned int _ticks_update;
};


#endif //__UONEWCLIENT_INPUT_H
