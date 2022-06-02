#ifndef GAMEROOM_H
#define GAMEROOM_H

#include "Socket.h"
#include "NetworkMessage.h"

class GameRoom
{
public:
    GameRoom(Socket* server,std::string code, Socket *player, std::string playerNick);
    ~GameRoom();
    bool isRoomFull();
    bool isRoomEmpty();
    bool isPlayerInRoom(Socket *socket);
    bool addPlayer(Socket *socket, std::string playerNick);
    void sendBroadcast(NetworkMessage &msg);
    void sendToOtherPlayer(Socket* player, NetworkMessage &msg);
    std::string getGameCode();
    Socket* getOtherPlayer(Socket *socket);

private:
    Socket* server;
    Socket *playerOne;
    Socket *playerTwo;
    std::string gameCode;
    std::string playerOneNick;
    std::string playerTwoNick;
};

#endif