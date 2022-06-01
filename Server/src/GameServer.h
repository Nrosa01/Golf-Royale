#ifndef GAMESERVER_H
#define GAMESERVER_H

#include "Socket.h"
#include <stdint.h>
#include <unordered_map>
#include "RoomSystem.h"

class GameServer
{
public:
    GameServer(const char *address, const char *port);

    void run();
    bool isConnected(Socket* socket);
    void addClient(Socket* clientSocket, char *msg);
    void removeClient(Socket* clientSocket);
private:
    Socket socket;
    RoomSystem clientManager;
};

#endif