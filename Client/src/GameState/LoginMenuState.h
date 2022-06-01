#ifndef LOGINMENUSTATE_H
#define LOGINMENUSTATE_H

#include "GameState.h"

class LoginMenuState : public GameState
{
public:
    LoginMenuState(SDLApp *app);
    virtual void onStateEnter();
    virtual ~LoginMenuState();

    Entity *inputField;
    Entity *gameCodeInputField;
    Entity* errorLabel;
private:
    std::function<void()> loginCallback();
    std::function<void()> exitStateCallback();
};

#endif