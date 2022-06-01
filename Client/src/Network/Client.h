#ifndef CLIENT_H
#define CLIENT_H

#include "Socket.h"
class NetworkMessage;

class Client
{
public:
    Client(const char *address, const char *port);

    void logout();
    void send(NetworkMessage &msg);
    void send(NetworkMessage &&msg);
    void setUsername(const char *username);

private:
    Socket socket;
    std::string clientName;
};

#endif