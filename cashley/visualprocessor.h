//
// Created by rot on 11/10/16.
//

#ifndef __UONEWCLIENT_VISUALPROCESSOR_H
#define __UONEWCLIENT_VISUALPROCESSOR_H

#include <cashley/cashley.h>

#include "../common/debug.h"

class VisualProcessor : public CAshley::Processor {
    public:
        virtual void run_tick(unsigned int delay);
        CASHLEY_PROCESSOR
};

#endif //__UONEWCLIENT_VISUALPROCESSOR_H
