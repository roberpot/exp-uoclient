//
// Created by rot on 13/10/16.
//

#ifndef __UONEWCLIENT_ARTIFACT_H
#define __UONEWCLIENT_ARTIFACT_H

#include "../common/debug.h"

class Artifact {
public:
    virtual void move(int x, int y, int z);
    virtual void drag(int x, int y);
    virtual void left_click();
    virtual void right_click();
    virtual void left_down();
    virtual void right_down();
    virtual void left_up();
    virtual void right_up();
    virtual void over();
    virtual void blur();
    virtual ~Artifact() { }
private:
};


#endif //__UONEWCLIENT_ARTIFACT_H
