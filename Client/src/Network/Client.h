#ifndef CLIENT_H
#define CLIENT_H

//#include "Socket.h"
#include <thread>
#include <queue>
#include <mutex>
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
    std::mutex messages_mutex;

    std::thread net_thread;
    void net_thread_f();
};

#endif