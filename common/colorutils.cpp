//
// Created by rot on 10/11/16.
//

#include "debug.h"

float default_color[4] = {0.0f, 0.0f, 0.0f, 0.0f};

void color32_to_fv4(unsigned int c, float * v) {
    v[3] = 0.00392157f * float((c >> 24) & 0x000000FF);
    v[0] = 0.00392157f * float((c >> 16) & 0x000000FF);
    v[1] = 0.00392157f * float((c >> 8) & 0x000000FF);
    v[2] = 0.00392157f * float(c & 0x000000FF);
}
