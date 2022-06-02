#ifndef PLAYSTATE_H
#define PLAYSTATE_H

#include "GameState.h"

class PlayState : public GameState
{
public:
    PlayState(SDLApp *app, std::string enemyNick = "Test");
    virtual ~PlayState(){};
    virtual void receiveNetworkMessage(NetworkMessage& msg);
    virtual void onStateExit();
private:
};

#endif