//
// Created by rot on 24/10/16.
//

#ifndef __UONEWCLIENT_ENTRY3D_H
#define __UONEWCLIENT_ENTRY3D_H

#define PACK_NEEDED __attribute__ ((packed))

struct Entry3D {
    Entry3D() : lookup(-1), length(-1), extra(-1) {}
    int lookup;
    int length;
    int extra;
} PACK_NEEDED;

#undef PACK_NEEDED

#endif //__UONEWCLIENT_ENTRY3D_H
