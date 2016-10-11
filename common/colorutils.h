//
// Created by rot on 10/10/16.
//

#ifndef __UONEWCLIENT_COLORUTILS_H
#define __UONEWCLIENT_COLORUTILS_H

#define color16_to_color32(x) (((((x) >> 10) & 0x1F) * 0xFF / 0x1F) | (((((x) >> 5) & 0x1F) * 0xFF / 0x1F) << 8) | ((((x) & 0x1F) * 0xFF / 0x1F) << 16))

#endif //__UONEWCLIENT_COLORUTILS_H
