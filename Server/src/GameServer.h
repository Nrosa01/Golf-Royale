#ifndef GAMESERVER_H
#define GAMESERVER_H

#include "Socket.h"
#include <stdint.h>

class GameServer
{
public:
    GameServer(const char *address, const char *port);

    void run();
    uint8_t getType(char* data);
private:
    Socket socket;
};

#endif