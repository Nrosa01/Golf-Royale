#ifndef LOBBYSTATE_H
#define LOBBYSTATE_H

#include "GameState.h"

class LobbyState : public GameState
{
public:
    LobbyState(SDLApp *app);
    virtual ~LobbyState();
};

#endif