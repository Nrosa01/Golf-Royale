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
        char *msg = socket.recv(clientSocket);

        if (msg == nullptr)
        {
            std::cerr << "Recv: Error al recibir mensaje\n";
            continue;
        }

        MessageType msgType = (MessageType)getType(msg);

        switch (msgType)
        {
        case MessageType::LOGIN:
        {
            LoginMessage login;
            login.from_bin(msg);
            std::cout << "Recv: Mensaje de tipo LOGIN " << login.loginCode << "\n";
            break;
        }
        case MessageType::LOGOUT:
            std::cout << "Recv: Mensaje de tipo LOGOUT\n";
            break;
        case MessageType::LEVEL_END:
            std::cout << "Recv: Mensaje de tipo LEVEL_END\n";
            break;
        case MessageType::BALL_HIT:
            std::cout << "Recv: Mensaje de tipo BALL_HIT\n";
            break;
        default:
            std::cerr << "Recv: Mensaje de tipo desconocido\n";
            break;
        }
    }
}

uint8_t GameServer::getType(char *data)
{
    if (data == nullptr || strlen(data) < sizeof(uint8_t))
        return 0;

    uint8_t type;
    memcpy(&type, data, sizeof(uint8_t));

    return type;
}