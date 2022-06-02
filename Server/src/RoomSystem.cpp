#include "RoomSystem.h"
#include <iostream>

RoomSystem::RoomSystem(Socket *server) : server(server) {}

RoomSystem::~RoomSystem()
{
    for (auto it = rooms.begin(); it != rooms.end(); ++it)
        delete it->second;

    rooms.clear();
    clients.clear();
}

bool RoomSystem::roomExists(std::string code)
{
    return rooms.find(code) != rooms.end();
}

bool RoomSystem::isPlayerInRoom(Socket *player)
{
    return clients.find(player->getHashId()) != clients.end();
}

bool RoomSystem::isRoomFull(std::string code)
{
    if (!roomExists(code))
        return logError("Room does not exist");
    else
        return rooms.at(code)->isRoomFull();
}

bool RoomSystem::addPlayer(Socket *player, std::string code, std::string playerNick)
{
    if (code.empty())
        return logError("Error: Code is empty");

    if (roomExists(code))
    {
        GameRoom *room = rooms.at(code);
        if (room->isRoomFull() || isPlayerInRoom(player))
            return logError("Room is full or player is already in room");

        clients.insert(std::pair<SocketID, GameRoom *>(player->getHashId(), room));
        room->addPlayer(player, playerNick);
    }
    else
    {
        GameRoom *room = new GameRoom(server, code, player, playerNick);
        rooms.insert(std::pair<std::string, GameRoom *>(code, room));
        clients.insert(std::pair<SocketID, GameRoom *>(player->getHashId(), room));
    }

    return true;
}

bool RoomSystem::removePlayer(Socket *player)
{
    if (isPlayerInRoom(player))
    {
        GameRoom *room = clients.at(player->getHashId());
        clients.erase(player->getHashId());
        rooms.erase(room->getGameCode());

        Socket *other = room->getOtherPlayer(player);
        if (other != nullptr)
            clients.erase(other->getHashId());

        delete room;
        return true;
    }
    else
        return logError("Error removing player, player not in any room");
}

bool RoomSystem::sendMessageToOtherPlayer(Socket *playerWhoSends, NetworkMessage &msg)
{
    if (isPlayerInRoom(playerWhoSends))
    {
        GameRoom *room = clients.at(playerWhoSends->getHashId());
        Socket *otherPlayer = room->getOtherPlayer(playerWhoSends);
        if (otherPlayer != nullptr)
        {
            server->send(msg, *otherPlayer);
            return true;
        }
        else
            return logError("Can't send message to other player, other player is null");
    }
    else
        return logError("Player not in any room");
}

bool RoomSystem::logError(std::string msg)
{
    std::cout << msg << std::endl;
    return false;
}

uint32_t RoomSystem::getPlayerCount()
{
    return clients.size();
}