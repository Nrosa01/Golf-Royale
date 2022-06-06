#include "LoginMenuState.h"
#include "../EC/Entity.h"
#include "../EC/Components/Renderer.h"
#include "../EC/Components/Transform.h"
#include "../SDLUtils/SDLApp.h"
#include "../EC/Components/Button.h"
#include "../EC/Components/TextField.h"
#include "../EC/Components/Transitioner.h"
#include "../EC/Components/TextRenderer.h"
#include "LobbyState.h"
#include <iostream>

LoginMenuState::LoginMenuState(SDLApp *app) : GameState(app)
{
    int width = app->getWidth();
    int height = app->getHeight();

    createEntity(Vector2D(width / 2, height / 2), Vector2D(1, 1), "menuBg");

    Entity *lobbyTittle = createEntity(Vector2D(width / 2, 75), Vector2D(1, 1), "button");
    lobbyTittle->aAddComponent(new TextRenderer("Lobby", "toonFont", 72));

    inputField = createEntity(Vector2D(width / 2 + 125, height / 2 - 100), Vector2D(0.5f, 1));
    inputField->aAddComponent(new TextField(app->getTexture("button"), "toonFont", 72, 8));

    Entity *inputLabel = createEntity(Vector2D(width / 2 - 125, height / 2 - 100), Vector2D(0.4, 0.5), "button");
    inputLabel->aAddComponent(new TextRenderer("Ingrese su nombre:", "toonFont", 24));

    gameCodeInputField = createEntity(Vector2D(width / 2 + 125, height / 2), Vector2D(0.5f, 1));
    gameCodeInputField->aAddComponent(new TextField(app->getTexture("button"), "toonFont", 72));

    Entity *gameCodeInputLabel = createEntity(Vector2D(width / 2 - 125, height / 2), Vector2D(0.4, 0.5), "button");
    gameCodeInputLabel->aAddComponent(new TextRenderer("Codigo del juego:", "toonFont", 24));

    Entity *exitButton = createEntity(Vector2D(width / 2, height / 2 + 200), Vector2D(0.5f, 1));
    exitButton->aAddComponent(new Button(app->getTexture("button"), "Menu", "toonFont", 72, exitStateCallback()));

    Entity *startButton = createEntity(Vector2D(width / 2, height / 2 + 100), Vector2D(0.5f, 1));
    startButton->aAddComponent(new Button(app->getTexture("button"), "Unirse", "toonFont", 72, loginCallback()));

    errorLabel = createEntity(Vector2D(width / 2, height / 2 + 275), Vector2D(0.5f, 0.5f), "button");
    errorLabel->aAddComponent(new TextRenderer("Introduzca nombre y codigo", "toonFont", 24, {255, 0, 0}));

    addTransitioner(exitButton);
    addTransitioner(inputField);
    addTransitioner(inputLabel);
    addTransitioner(gameCodeInputField);
    addTransitioner(gameCodeInputLabel);
    addTransitioner(startButton);
    addTransitioner(lobbyTittle);
    addTransitioner(errorLabel);
}

LoginMenuState::~LoginMenuState() {}

std::function<void()> LoginMenuState::loginCallback()
{
    return [this]()
    {
        std::string name = inputField->getComponent<TextField>()->getText();
        std::string gameCode = gameCodeInputField->getComponent<TextField>()->getText();
        uint requiredCodeLenght = gameCodeInputField->getComponent<TextField>()->getMaxLength();

        if (name.empty() || gameCode.size() < requiredCodeLenght)
        {
            errorLabel->getComponent<Transitioner>()->startScale();
            return;
        }

        if (this->errorLabel->getTransform()->getScale().x < 0.1f)
            errorLabel->getComponent<Transitioner>()->disable();

        startExitTransitionTimer([this, name, gameCode](GameState *gmState, void *args)
                                 {
            this->getApp()->setPlayerName(name);
            LobbyState* lobby = new LobbyState(this->getApp());
            lobby->setGameCode(gameCode);
            
            this->getApp()->pushState(lobby); });
    };
}

std::function<void()> LoginMenuState::exitStateCallback()
{
    return [this]()
    {
        errorLabel->getComponent<Transitioner>()->disable();
        startExitTransitionTimer(popState);
    };
}

void LoginMenuState::onStateEnter()
{
    GameState::onStateEnter();
    errorLabel->getComponent<Transitioner>()->stop();
    errorLabel->getComponent<Transitioner>()->enable();

    if (this->getApp()->getPlayerName() != "")
        this->inputField->getComponent<TextField>()->setText(this->getApp()->getPlayerName());
}