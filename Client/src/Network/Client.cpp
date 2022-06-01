#include "Client.h"
#include "NetworkMessage.h"
#include <iostream>

Client::Client(const char *address, const char *port) : socket(address, port)
{}

void Client::logout()
{
    NetworkMessage msg;
    msg.type = MessageType::LOGOUT;
    socket.send(msg, socket);
}

void Client::send(NetworkMessage &msg)
{
    socket.send(msg, socket);
}

void Client::setUsername(const char *username)
{
    clientName = username;
}