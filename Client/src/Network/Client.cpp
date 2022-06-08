#include "Client.h"
#include "NetworkMessage.h"
#include <iostream>

Client::Client(const char *address, const char *port) : /*socket(address, port),*/ connected(true), terminated(false)
{
    // this->net_thread = std::thread([this]()
    //                                { this->net_thread_f(); });
}

Client::~Client()
{
    terminated = true;
    // socket.close();
    // net_thread.join();

    while (!messages.empty())
    {
        delete messages.front();
        messages.pop();
    }
}

void Client::connect()
{
    connected = true;
}

void Client::disconnect()
{
    connected = false;
}

void Client::send(NetworkMessage &msg)
{
    //socket.send(msg, socket);
}

void Client::net_thread_f()
{
    char *msg;

    while (!terminated)
    {
        if (!connected)
            continue;

        //msg = socket.recv();

        if (msg == nullptr && !terminated)
        {
            std::cout << "Recv Client: Error al recibir mensaje\n";
            continue;
        }

        MessageType msgType = getType(msg);

        switch (msgType)
        {
        case PLAYER_JOINED:
        {
            PlayerJoinedMessage *playerJoinedMessage = new PlayerJoinedMessage();
            playerJoinedMessage->from_bin(msg);

            messages_mutex.lock();
            messages.push(playerJoinedMessage);
            messages_mutex.unlock();
            break;
        }
        case BALL_POS:
        {
            BallPosMessage *ballHitMessage = new BallPosMessage(0, 0);
            ballHitMessage->from_bin(msg);

            messages_mutex.lock();
            messages.push(ballHitMessage);
            messages_mutex.unlock();
        }
        break;
        case ERROR_MESSAGE:
            std::cout << "Recv Client: Mensaje de tipo ERROR_MESSAGE \n";
            break;
        default:
        {
            NetworkMessage *netMsg = new NetworkMessage(msgType);

            messages_mutex.lock();
            messages.push(netMsg);
            messages_mutex.unlock();
        }
        break;
        }
    }
}

NetworkMessage *Client::consumeMessage()
{
    if (messages.empty())
        return nullptr;

    messages_mutex.lock();

    NetworkMessage *msg = messages.front();
    messages.pop();

    messages_mutex.unlock();
    return msg;
}
