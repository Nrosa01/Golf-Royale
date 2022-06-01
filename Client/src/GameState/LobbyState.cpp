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
#include <iostream>

LobbyState::LobbyState(SDLApp *app) : GameState(app)
{
    int width = app->getWidth();
    int height = app->getHeight();

    createEntity(Vector2D(width / 2, height / 2), Vector2D(1, 1), "menuBg");

    Entity* lobbyTittle = createEntity(Vector2D(width / 2, 75), Vector2D(1, 1), "button");
    lobbyTittle->AddComponent(new TextRenderer("Lobby", "toonFont", 72));
    
    nameLabel = createEntity(Vector2D(width / 2 - 125, height/ 2 - 100), Vector2D(0.4, 1), "button");
    nameLabel->AddComponent(new TextRenderer("Empty:", "toonFont", 72));

    gameCodeLabel = createEntity(Vector2D(width / 2 + 125, height/ 2 - 100), Vector2D(0.4, 1), "button");
    gameCodeLabel->AddComponent(new TextRenderer("Code:", "toonFont", 72));

    Entity *exitButton = createEntity(Vector2D(width / 2, height/ 2 + 200), Vector2D(0.5f, 1));
    exitButton->AddComponent(new Button(app->getTexture("button"), "Volver", "toonFont", 72, [this]()
    {
        startExitTransitionTimer(popState);
    }));

    addTransitioner(exitButton);
    addTransitioner(nameLabel);
    addTransitioner(gameCodeLabel);
    addTransitioner(lobbyTittle);
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

    this->sendNetworkMessage(LoginMessage(gameCode));
}

void LobbyState::onStateExit()
{
    GameState::onStateExit();
    this->sendNetworkMessage(NetworkMessage(LOGOUT));
}