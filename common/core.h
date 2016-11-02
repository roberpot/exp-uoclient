//
// Created by rot on 2/11/16.
//

#ifndef __UONEWCLIENT_CORE_H
#define __UONEWCLIENT_CORE_H

#include <map>

#include "../artifacts/form.h"

extern class Core {
public:
    Core();
    unsigned int add_form(Form * f);
    unsigned int enable_form(unsigned int uid);
    bool is_focused(unsigned int layer);
    unsigned int focus(unsigned int layer);
private:
    unsigned int _form_uids, _highest_layer;
    std::map<unsigned int, Form *> _forms, _displayed_forms;
//    std::map<
} core;

#endif //__UONEWCLIENT_CORE_H
