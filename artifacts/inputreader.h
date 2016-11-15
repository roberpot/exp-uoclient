//
// Created by rot on 14/11/16.
//

#ifndef __UONEWCLIENT_INPUTREADER_H
#define __UONEWCLIENT_INPUTREADER_H

#include "../common/key.h"

class InputReader {
public:
    void focus();
    void blur();
    void force_blur();
    virtual void get_char(Key k) = 0;
protected:
    virtual void _focus() = 0;
    virtual void _blur() = 0;
private:
};

#endif //__UONEWCLIENT_INPUTREADER_H
