//
// Created by rot on 31/10/16.
//

#ifndef __UONEWCLIENT_DISPLAYLIST_H
#define __UONEWCLIENT_DISPLAYLIST_H


#include <GL/gl.h>
#ifdef __MINGW32__
#include <GL/glext.h>
#endif

#include "resourcereferencer.h"


class DisplayList : public AutoRemovedResource {
public:
    DisplayList();
    ~DisplayList();
    void init_compilation();
    void end_compilation();
    inline void display() { glCallList(_dl); }
private:
    unsigned int _dl;
};


#endif //__UONEWCLIENT_DISPLAYLIST_H
