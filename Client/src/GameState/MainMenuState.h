#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include "GameState.h"

class MainMenuState : public GameState
{
public:
    MainMenuState(SDLApp *app);
    virtual void update(float deltaTime);
    virtual ~MainMenuState(){};

private:
    bool startTransition;
    float timer;
};

#endif