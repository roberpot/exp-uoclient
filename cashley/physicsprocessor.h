//
// Created by rot on 13/10/2016.
//

#ifndef __UONEWCLIENT_PHYSICSPROCESSOR_H
#define __UONEWCLIENT_PHYSICSPROCESSOR_H

#include <cashley/cashley.h>

class PhysicsProcessor : public CAshley::Processor {
public:
    virtual void run_tick(unsigned int delay);
    CASHLEY_PROCESSOR
};

#endif //__UONEWCLIENT_PHYSICSPROCESSOR_H
