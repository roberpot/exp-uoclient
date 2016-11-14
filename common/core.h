//
// Created by rot on 2/11/16.
//

#ifndef __UONEWCLIENT_CORE_H
#define __UONEWCLIENT_CORE_H

#include <map>

#include "../artifacts/form.h"
#include "../artifacts/inputreader.h"

extern class Core {
public:
    Core();
    unsigned int add_form(Form * f);
    int enable_form(unsigned int uid);
    bool is_focused(int layer);
    int focus(int layer);
    bool try_to_focus(InputReader * i);
    void blur(InputReader * i);
private:
    unsigned int _form_uids;
    int _highest_layer;
    std::map<int, Form *> _forms, _displayed_forms;
    InputReader * _input;
//    std::map<
} core;

#endif //__UONEWCLIENT_CORE_H
