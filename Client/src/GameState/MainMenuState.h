#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include "GameState.h"

class MainMenuState : public GameState
{
public:
    MainMenuState(SDLApp* app);
    virtual ~MainMenuState(){};
};

#endif