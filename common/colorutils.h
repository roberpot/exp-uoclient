//
// Created by rot on 10/10/16.
//

#ifndef __UONEWCLIENT_COLORUTILS_H
#define __UONEWCLIENT_COLORUTILS_H

extern float default_color[4];

#define color16_to_color32(x) (unsigned int)(((((x) >> 10) & 0x1F) * 0xFF / 0x1F) | (((((x) >> 5) & 0x1F) * 0xFF / 0x1F) << 8) | ((((x) & 0x1F) * 0xFF / 0x1F) << 16))
#define is_gray(x) (bool)(((x) & 0x1F) == (((x) >> 5) & 0x1F) && ((x) & 0x1F) == (((x) >> 10) & 0x1F))
#define color16_to_color32_gray(x)  (((unsigned int)((x) >> 10) & 0x0000001F) | 0x80000000)
#define get_huetable_lookup(x)  (((unsigned short)((x) >> 10) & 0x001F))

void color32_to_fv4(unsigned int c, float * v);

#endif //__UONEWCLIENT_COLORUTILS_H
