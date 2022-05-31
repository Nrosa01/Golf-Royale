#include "Client.h"
#include "NetworkMessage.h"
#include <iostream>

Client::Client(const char *address, const char *port) : socket(address, port)
{
    std::cout << "Client Init" << std::endl;
}

void Client::login()
{
    NetworkMessage msg;
    msg.type = MessageType::LOGIN;
    socket.send(msg, socket);
}

void Client::logout()
{
    NetworkMessage msg;
    msg.type = MessageType::LOGOUT;
    socket.send(msg, socket);
}