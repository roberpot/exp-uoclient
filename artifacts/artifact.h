//
// Created by rot on 13/10/16.
//

#ifndef __UONEWCLIENT_ARTIFACT_H
#define __UONEWCLIENT_ARTIFACT_H


class Artifact {
public:
    virtual void left_click();
    virtual void right_click();
    virtual void left_release();
    virtual void right_release();
private:
};


#endif //__UONEWCLIENT_ARTIFACT_H
