#ifndef CLIENT_H
#define CLIENT_H

//#include "Socket.h"
#include <queue>
#include <SDL2/SDL_thread.h>
#include <SDL2/SDL_mutex.h>
#define MAX_MESSAGE_LIVE_SECONDS 5
class NetworkMessage;

class Client
{
public:
    Client(const char *address, const char *port);
    ~Client();

    void send(NetworkMessage &msg);
    void connect();
    void disconnect();
    NetworkMessage* consumeMessage();

private:
    //Socket socket;
    bool connected;
    bool terminated;
    std::queue<NetworkMessage*> messages;
    SDL_mutex* messages_mutex;

    SDL_Thread* net_thread;
    void net_thread_f();
};

#endif