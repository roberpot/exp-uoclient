//
// Created by rot on 2/11/16.
//

#include "../engines/video.h"
#include "../engines/input.h"

#include "../resources/font.h"
#include "../resources/gump.h"
#include "../resources/hues.h"

#include "debug.h"

#include "core.h"

InputEngine input;
VideoEngine video;

FontManager fontmanager;
GumpManager gumpmanager;
HuesManager huesmanager;

Core core;

Core::Core() {
    _form_uids = 0;
    _highest_layer = 0;
}

unsigned int Core::add_form(Form * f) {
    _forms[_form_uids] = f;
    return _form_uids++;
}

unsigned int Core::enable_form(unsigned int uid) {
    Form * f = _forms[uid];
    _highest_layer += 1000;
    _displayed_forms[_highest_layer] = f;
    return _highest_layer;
}

bool Core::is_focused(unsigned int layer) {
    return layer == _highest_layer;
}

unsigned int Core::focus(unsigned int layer) {
    Form * f = _displayed_forms[layer];
    _highest_layer += 1000;
    _displayed_forms.erase(layer);
    _displayed_forms[_highest_layer] = f;
    return _highest_layer;
}