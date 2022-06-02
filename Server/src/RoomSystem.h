#ifndef ROOMSYSTEM_H
#define ROOMSYSTEM_H

#include "GameRoom.h"
#include "NetworkMessage.h"
#include <unordered_map>
using namespace std;

class RoomSystem
{
public:
    RoomSystem(Socket* server);
    ~RoomSystem();
    bool roomExists(std::string code);
    bool isPlayerInRoom(Socket *player);
    bool isRoomFull(std::string code);
    std::string getGameCode(Socket *player);
    std::string getClientName(Socket *player);

    // Estas operaciones pueden fallar, por eso son bool
    bool addPlayer(Socket *player, std::string code, std::string playerNick);
    bool removePlayer(Socket *player);
    bool sendMessageToOtherPlayer(Socket *playerWhoSends, NetworkMessage &msg);
    uint32_t getPlayerCount();
private:
    Socket *server;
    unordered_map<string, GameRoom *> rooms;
    unordered_map<SocketID, GameRoom *> clients;
    
    bool logError(std::string msg);
};

#endif