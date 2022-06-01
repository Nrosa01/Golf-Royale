#include "GameRoom.h"

GameRoom::GameRoom(std::string code, Socket *player)
{
    gameCode = code;
    playerOne = player;
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
bool GameRoom::addPlayer(Socket *socket)
{
    if (playerOne == nullptr || playerOne->getHashId() == socket->getHashId())
        return false;

    if (playerTwo == nullptr)
        playerTwo = socket;
    else
        return false;

    return playerTwo != nullptr;
}

std::string GameRoom::getGameCode()
{
    return gameCode;
}

Socket* GameRoom::getOtherPlayer(Socket *socket)
{
    if (socket == playerOne)
        return playerTwo;
    else if (socket == playerTwo)
        return playerOne;
    else
        return nullptr;
}