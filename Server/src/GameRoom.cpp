#include "GameRoom.h"

GameRoom::GameRoom(Socket* server, std::string code, Socket *player, std::string playerNick)
{
    this->server = server;
    gameCode = code;
    playerOne = player;
    playerOneNick = playerNick;
}

GameRoom::~GameRoom()
{
    NetworkMessage msg(PLAYER_DISCONNECTED);
    sendBroadcast(msg);

    playerOne = nullptr;
    playerTwo = nullptr;
}

bool GameRoom::isRoomFull()
{
    return playerTwo != nullptr && playerOne != nullptr;
}

bool GameRoom::isRoomEmpty()
{
    return playerOne == nullptr && playerTwo == nullptr;
}

bool GameRoom::isPlayerInRoom(Socket *socket)
{
    return socket == playerOne || socket == playerTwo;
}

// If there is no host, then it fails, there must always be a host
bool GameRoom::addPlayer(Socket *socket, std::string playerNick)
{
    if (playerOne == nullptr || socket == nullptr || *playerOne == *socket)
        return false; // Room is corrupt

    if (playerTwo != nullptr)
        return false; // Room is full

    playerTwo = socket;
    playerTwoNick = playerNick;

    PlayerJoinedMessage msg(playerOneNick);
    server->send(msg, *playerTwo);

    msg.playerNick = playerTwoNick;
    server->send(msg, *playerOne);

    return true;
}

std::string GameRoom::getGameCode()
{
    return gameCode;
}

Socket *GameRoom::getOtherPlayer(Socket *socket)
{
    if (!isRoomFull())
        return nullptr;

    if (*socket == *playerOne)
        return playerTwo;
    else if (*socket == *playerTwo)
        return playerOne;
    else
        return nullptr;
}

void GameRoom::sendBroadcast(NetworkMessage &msg)
{
    if (playerOne != nullptr)
        server->send(msg, *playerOne);
    if (playerTwo != nullptr)
        server->send(msg, *playerTwo);
}

void GameRoom::sendToOtherPlayer(Socket *player, NetworkMessage &msg)
{
    Socket *other = getOtherPlayer(player);

    if (other != nullptr)
        server->send(msg, *other);
}