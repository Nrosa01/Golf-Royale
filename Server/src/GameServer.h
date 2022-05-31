#ifndef GAMESERVER_H
#define GAMESERVER_H

#include "Socket.h"
#include <stdint.h>
#include <unordered_map>

class GameServer
{
public:
    GameServer(const char *address, const char *port);

    void run();
    uint8_t getType(char* data);
    bool isConnected(Socket* socket);
private:
    Socket socket;

    // Hash to socket, to find connected clients
    std::unordered_map<uint32_t, Socket*> clients;
};

#endif