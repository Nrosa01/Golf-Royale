#ifndef CLIENT_H
#define CLIENT_H

#include "Socket.h"

class Client
{
public:
    Client(const char *address, const char *port);

    //void run();
    void login();
    void logout();

private:
    Socket socket;
};

#endif