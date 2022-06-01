#ifndef GAMEROOM_H
#define GAMEROOM_H

#include "Socket.h"

class GameRoom
{
public:
    GameRoom(std::string code, Socket *player);
    bool isRoomFull();
    bool isRoomEmpty();
    bool isPlayerInRoom(Socket *socket);
    bool addPlayer(Socket *socket);
    std::string getGameCode();
    Socket* getOtherPlayer(Socket *socket);

private:
    Socket *playerOne;
    Socket *playerTwo;
    std::string gameCode;
};

#endif