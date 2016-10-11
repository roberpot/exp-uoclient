//
// Created by rot on 10/10/16.
//

#ifndef __UONEWCLIENT_UTILS_H
#define __UONEWCLIENT_UTILS_H

#include "types.h"

unsigned int change_endian(unsigned int i);
uo_uword change_endian(uo_uword i);
void print_raw(uo_byte * raw, unsigned int l);
void display_textured_square(int x, int y, int w, int h, int z, unsigned int t);
void display_colored_square(int x, int y, int w, int h, int z, unsigned int c);

#endif //__UONEWCLIENT_UTILS_H
