//
// Created by rot on 16/10/2016.
//

#ifndef __UONEWCLIENT_INPUTPROCESSOR_H
#define __UONEWCLIENT_INPUTPROCESSOR_H


#include <cashley/cashley.h>


class InputProcessor : public CAshley::Processor {
public:
    virtual void run_tick(unsigned int delay);
    CASHLEY_PROCESSOR
};

#endif //__UONEWCLIENT_INPUTPROCESSOR_H
