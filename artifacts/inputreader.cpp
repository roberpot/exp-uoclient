//
// Created by rot on 14/11/16.
//

#include "inputreader.h"
#include "../common/core.h"

void InputReader::focus() {
    if (core.try_to_focus(this)) {
        _focus();
    }
}

void InputReader::blur() {
    _blur();
}

void InputReader::force_blur() {
    core.blur(this);
}