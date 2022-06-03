#ifndef ENDSTATE_H
#define ENDSTATE_H

#include "GameState.h"

class EndState : public GameState
{
public:
    EndState(SDLApp *app, uint8_t playerScore, uint8_t enemyScore);
    virtual ~EndState();
    virtual void onStateEnter();
};

#endif