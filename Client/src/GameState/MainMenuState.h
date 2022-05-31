#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include "GameState.h"
class Transitioner;

class MainMenuState : public GameState
{
public:
    MainMenuState(SDLApp *app);
    virtual void update(float deltaTime);
    virtual ~MainMenuState(){};
    void startTransitionTimer();

private:
    vector<Transitioner *> transitioners;
    bool startTransition;
    float timer;
};

#endif