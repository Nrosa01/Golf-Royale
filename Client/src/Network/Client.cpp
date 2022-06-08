#include "Client.h"
#include "NetworkMessage.h"
#include <iostream>

Client::Client(const char *address, const char *port) : /*socket(address, port),*/ connected(true), terminated(false)
{
    // this->net_thread = std::thread([this]()
    //                                { this->net_thread_f(); });
    this->messages_mutex = SDL_CreateMutex();
    SDL_ThreadFunction net_thread_f = [](void* args)
    {
        Client* client = (Client*)args;
        client->net_thread_f();
        return 0;
    };
    this->net_thread = SDL_CreateThread(net_thread_f, "net_thread", this);
}

Client::~Client()
{
    terminated = true;
    SDL_WaitThread(net_thread, NULL);
    SDL_DestroyMutex(messages_mutex);
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
    // socket.send(msg, socket);
}

void Client::net_thread_f()
{
    char *msg = nullptr;

    while (!terminated)
    {
        if (!connected)
            continue;

        // msg = socket.recv();

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

            SDL_LockMutex(messages_mutex);
            messages.push(playerJoinedMessage);
            SDL_UnlockMutex(messages_mutex);
            break;
        }
        case BALL_POS:
        {
            BallPosMessage *ballHitMessage = new BallPosMessage(0, 0);
            ballHitMessage->from_bin(msg);

            SDL_LockMutex(messages_mutex);
            messages.push(ballHitMessage);
            SDL_UnlockMutex(messages_mutex);
        }
        break;
        case ERROR_MESSAGE:
            std::cout << "Recv Client: Mensaje de tipo ERROR_MESSAGE \n";
            break;
        default:
        {
            NetworkMessage *netMsg = new NetworkMessage(msgType);

            SDL_LockMutex(messages_mutex);
            messages.push(netMsg);
            SDL_UnlockMutex(messages_mutex);
        }
        break;
        }
    }
}

NetworkMessage *Client::consumeMessage()
{
    SDL_LockMutex(messages_mutex);
    if (messages.empty())
    {
        SDL_UnlockMutex(messages_mutex);
        return nullptr;
    }


    NetworkMessage *msg = messages.front();
    messages.pop();

    SDL_UnlockMutex(messages_mutex);
    return msg;
}
