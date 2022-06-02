#include "LobbyState.h"
#include "../EC/Entity.h"
#include "../EC/Components/Renderer.h"
#include "../EC/Components/Transform.h"
#include "../SDLUtils/SDLApp.h"
#include "../EC/Components/Button.h"
#include "../EC/Components/TextField.h"
#include "../EC/Components/Transitioner.h"
#include "../EC/Components/TextRenderer.h"
#include "MainMenuState.h"
#include "PlayState.h"
#include <iostream>

LobbyState::LobbyState(SDLApp *app) : GameState(app)
{
    int width = app->getWidth();
    int height = app->getHeight();

    createEntity(Vector2D(width / 2, height / 2), Vector2D(1, 1), "menuBg");

    Entity *lobbyTittle = createEntity(Vector2D(width / 2, 75), Vector2D(1, 1), "button");
    lobbyTittle->AddComponent(new TextRenderer("Lobby", "toonFont", 72));

    nameLabel = createEntity(Vector2D(width / 2 - 125, height / 2 - 100), Vector2D(0.4, 1), "button");
    nameLabel->AddComponent(new TextRenderer("Empty:", "toonFont", 72));

    gameCodeLabel = createEntity(Vector2D(width / 2 + 125, height / 2 - 100), Vector2D(0.4, 1), "button");
    gameCodeLabel->AddComponent(new TextRenderer("Code:", "toonFont", 72));

    Entity *exitButton = createEntity(Vector2D(width / 2, height / 2 + 200), Vector2D(0.5f, 1));
    exitButton->AddComponent(new Button(app->getTexture("button"), "Volver", "toonFont", 72, [this]()
                                        { 
                                            NetworkMessage logout = NetworkMessage(LOGOUT);
                                            this->sendNetworkMessage(logout);
                                            startExitTransitionTimer(popState); }));

    Entity* waitForPlayerLabel = createEntity(Vector2D(width / 2, height / 2 + 50), Vector2D(1.35f, 1), "button");
    waitForPlayerLabel->AddComponent(new TextRenderer("Esperando jugadores...", "toonFont", 72));

    addTransitioner(exitButton);
    addTransitioner(nameLabel);
    addTransitioner(gameCodeLabel);
    addTransitioner(lobbyTittle);
    addTransitioner(waitForPlayerLabel);
}

LobbyState::~LobbyState() {}

void LobbyState::setGameCode(std::string gameCode)
{
    this->gameCode = gameCode;
}

std::string LobbyState::getGameCode()
{
    return gameCode;
}

void LobbyState::onStateEnter()
{
    GameState::onStateEnter();
    this->name = this->app->getPlayerName();

    this->nameLabel->GetComponent<TextRenderer>()->setText(this->name);
    this->gameCodeLabel->GetComponent<TextRenderer>()->setText(this->gameCode);

    LoginMessage login = LoginMessage(gameCode, name);
    this->sendNetworkMessage(login);
}

void LobbyState::receiveNetworkMessage(NetworkMessage &msg)
{
    GameState::receiveNetworkMessage(msg);

    if (msg.type == PLAYER_DISCONNECTED)
        startExitTransitionTimer(popState);
    else if (msg.type == PLAYER_JOINED)
    {
        PlayerJoinedMessage *message = &static_cast<PlayerJoinedMessage &>(msg);
        startExitTransitionTimer(changeState, new PlayState(app, message->playerNick));
    }
}