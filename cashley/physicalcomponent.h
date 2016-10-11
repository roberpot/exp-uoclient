//
// Created by rot on 11/10/16.
//

#ifndef __UONEWCLIENT_PHYSICALCOMPONENT_H
#define __UONEWCLIENT_PHYSICALCOMPONENT_H

#include <cashley/cashley.h>


class PhysicalComponent : public CAshley::Component {
public:
    void init() {};
    void shutdown() {};
    CASHLEY_COMPONENT
};

#endif //__UONEWCLIENT_PHYSICALCOMPONENT_H
