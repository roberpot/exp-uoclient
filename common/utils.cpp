#include <iostream>
#include <iomanip>


#include <GL/glew.h>
#include <GL/gl.h>

#include "../engines/video.h"

#include "debug.h"
#include "utils.h"


unsigned int change_endian(unsigned int i)
{
    unsigned int r = 0, t = 0;
    r = i >> 16;
    r &= 0x00FF;
    t = i << 16;
    t &= 0xFF00;
    r |= t;

    std::cout << "Original: " << std::endl;
    print_raw((uo_byte *)&i, 1);
    std::cout << "Procesado: " << std::endl;
    print_raw((uo_byte *)&r, 1);
    return r;
}

uo_uword change_endian(uo_uword i) {
    return i;
}

void print_raw(uo_byte * raw, unsigned int l) {
    std::cout << "DUMP: ";

    char prev_fill = std::cout.fill('0');

    for (unsigned int i = 0; i < l; i++) {
        std::cout << std::hex << std::setw(2) << ((unsigned short)raw[i] & 0x00FF )<< " ";
    }
    std::cout << std::dec << std::endl;
    std::cout.fill(prev_fill);
}

std::string int2hex_string(unsigned int i) {
    UNREFERENCED_PARAMETER(i);
    std::string a;
    return a;
}

void display_textured_square(int x, int y, int w, int h, int z, unsigned int t) {
    glPushMatrix();
    glTranslated(x, y, z);
    glBindTexture(GL_TEXTURE_2D, t);
    glBegin(GL_QUADS);
    glTexCoord2d(0, 0); glVertex2d(0, 0);
    glTexCoord2d(0, 1); glVertex2d(0, h);
    glTexCoord2d(1, 1); glVertex2d(w, h);
    glTexCoord2d(1, 0); glVertex2d(w, 0);
    glEnd();
    glPopMatrix();
}

void display_colored_square(int x, int y, int w, int h, int z, unsigned int c) {
    glPushMatrix();
    glTranslated(x, y, z);
    glColor4iv((int *)&c);
    glBegin(GL_QUADS);
    glVertex2d(0, 0);
    glVertex2d(0, h);
    glVertex2d(w, h);
    glVertex2d(w, 0);
    glEnd();
    glPopMatrix();
}
