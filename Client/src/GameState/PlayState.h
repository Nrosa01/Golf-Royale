#ifndef PLAYSTATE_H
#define PLAYSTATE_H

#include "GameState.h"

class PlayState : public GameState
{
public:
    PlayState(SDLApp* app);
    virtual ~PlayState(){};
};

#endif