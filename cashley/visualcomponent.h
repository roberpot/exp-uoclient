//
// Created by rot on 11/10/16.
//

#ifndef __UONEWCLIENT_VISUALCOMPONENT_H
#define __UONEWCLIENT_VISUALCOMPONENT_H

#include <cashley/cashley.h>


class VisualComponent : public CAshley::Component {
public:
    void init();
    void setup(int x, int y, int w, int h, int z, unsigned int texture, unsigned int flags);
    void shutdown();
    void display();
    CASHLEY_COMPONENT
private:
    unsigned int displaylist_id;
};

#endif //__UONEWCLIENT_VISUALCOMPONENT_H
