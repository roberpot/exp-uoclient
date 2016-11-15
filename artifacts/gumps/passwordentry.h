//
// Created by rot on 15/11/16.
//

#ifndef __UONEWCLIENT_PASSWORDENTRY_H
#define __UONEWCLIENT_PASSWORDENTRY_H

#include "textentry.h"

class PasswordEntry : public TextEntry {
public:
    CASHLEY_ENTITY
protected:
    void _focus();
    void _blur();
};

#endif //__UONEWCLIENT_PASSWORDENTRY_H
