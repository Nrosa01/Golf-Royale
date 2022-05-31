#include "GameServer.h"
#include "NetworkMessage.h"

GameServer::GameServer(const char *address, const char *port) : socket(address, port)
{
    socket.bind();
}

void GameServer::run()
{
    while (true)
    {
        Socket *clientSocket;
        char* msg = socket.recv(clientSocket);

        if (msg == nullptr)
        {
            std::cerr << "Recv: Error al recibir mensaje\n";
            continue;
        }
    }
}