#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include "GameState.h"
class Transitioner;

class MainMenuState : public GameState
{
public:
    MainMenuState(SDLApp *app);
    void onStateExit();
    virtual ~MainMenuState(){};
};

#endif