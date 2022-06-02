#ifndef LOBBYSTATE_H
#define LOBBYSTATE_H

#include "GameState.h"
class Entity;

class LobbyState : public GameState
{
public:
    LobbyState(SDLApp *app);
    virtual ~LobbyState();
    virtual void onStateEnter();
    virtual void receiveNetworkMessage(NetworkMessage& msg);
    void setGameCode(std::string gameCode);
    std::string getGameCode();

    Entity* nameLabel;
    Entity* gameCodeLabel;
private:
    std::string gameCode;
    std::string name;
};

#endif