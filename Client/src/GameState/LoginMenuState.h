#ifndef LOGINMENUSTATE_H
#define LOGINMENUSTATE_H

#include "GameState.h"

class LoginMenuState : public GameState
{
public:
    LoginMenuState(SDLApp* app);
    virtual ~LoginMenuState();
};

#endif