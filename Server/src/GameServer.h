#ifndef GAMESERVER_H
#define GAMESERVER_H

#include "Socket.h"

class GameServer
{
public:
    GameServer(const char *address, const char *port);

    void run();

private:
    Socket socket;
};

#endif