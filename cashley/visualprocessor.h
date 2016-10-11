//
// Created by rot on 11/10/16.
//

#ifndef UONEWCLIENT_VISUALPROCESSOR_H
#define UONEWCLIENT_VISUALPROCESSOR_H

#include <cashley/cashley.h>

#include "../common/debug.h"

class VisualProcessor : public CAshley::Processor {
    public:
        unsigned int counter;
        virtual void run_tick(unsigned int delay);
        CASHLEY_PROCESSOR
};

#endif //UONEWCLIENT_VISUALPROCESSOR_H
