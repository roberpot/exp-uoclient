//
// Created by rot on 13/10/16.
//

#ifndef __UONEWCLIENT_INPUT_H
#define __UONEWCLIENT_INPUT_H


#include "../common/debug.h"


#define INPUT_LBUTTON 0x01
#define INPUT_MBUTTON 0x02
#define INPUT_RBUTTON 0x04


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
    inline bool continue_execution() { return _continue_execution; }
    inline unsigned int collide_color() { return _collide_color; }
private:
    InputEngine();
    InputEngine(const InputEngine &v) { UNREFERENCED_PARAMETER(v); }
    void operator = (const InputEngine &v) { UNREFERENCED_PARAMETER(v); }
    static InputEngine _i;
    int _x, _y;
    unsigned char _mouse_status;
    bool _continue_execution;
    unsigned int _collide_color;
};


#endif //__UONEWCLIENT_INPUT_H
