//
// Created by rot on 15/11/16.
//

#include "passwordentry.h"
#include "../../resources/font.h"
#include "../../cashley/visualcomponent.h"
#include "../../common/utils.h"

void PasswordEntry::_focus() {
    std::string buffer = "*";
    buffer *= _buffer.length();
    if (_hues == -1) {
        _text = fontmanager.rasterize(_font, (buffer + '_').c_str());
    } else {
        _text = fontmanager.rasterize(_font, (buffer + '_').c_str(), _hues);
    }
    VisualComponent * vcomp = get_component<VisualComponent>();
    vcomp->shutdown();
    vcomp->init();
    vcomp->setup_with_dl(_x, _y, 0, _text);
    move(_lx, _ly, _lz);
}

void PasswordEntry::_blur() {
    std::string buffer = "*";
    buffer *= _buffer.length();
    if (_hues == -1) {
        _text = fontmanager.rasterize(_font, buffer.c_str());
    } else {
        _text = fontmanager.rasterize(_font, buffer.c_str(), _hues);
    }
    VisualComponent * vcomp = get_component<VisualComponent>();
    vcomp->shutdown();
    vcomp->init();
    vcomp->setup_with_dl(_x, _y, 0, _text);
    move(_lx, _ly, _lz);
}