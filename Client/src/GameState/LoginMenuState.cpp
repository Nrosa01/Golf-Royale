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

    Entity* lobbyTittle = createEntity(Vector2D(width / 2, 75), Vector2D(1, 1), "button");
    lobbyTittle->AddComponent(new TextRenderer("Lobby", "toonFont", 72));

    Entity* inputField = createEntity(Vector2D(width / 2 + 125, height/ 2 - 100), Vector2D(0.5f, 1));
    inputField->AddComponent(new TextField(app->getTexture("button"), "toonFont", 72, 8));

    Entity* inputLabel = createEntity(Vector2D(width / 2 - 125, height/ 2 - 100), Vector2D(0.4, 0.5), "button");
    inputLabel->AddComponent(new TextRenderer("Ingrese su nombre:", "toonFont", 24));

    Entity* gameCodeInputField = createEntity(Vector2D(width / 2 + 125, height/ 2), Vector2D(0.5f, 1));
    gameCodeInputField->AddComponent(new TextField(app->getTexture("button"), "toonFont", 72));

    Entity* gameCodeInputLabel = createEntity(Vector2D(width / 2 - 125, height/ 2), Vector2D(0.4, 0.5), "button");
    gameCodeInputLabel->AddComponent(new TextRenderer("Codigo del juego:", "toonFont", 24));


    Entity *exitButton = createEntity(Vector2D(width / 2, height/ 2 + 200), Vector2D(0.5f, 1));
    exitButton->AddComponent(new Button(app->getTexture("button"), "Menu", "toonFont", 72, [this]()
                                        { startExitTransitionTimer(popState); }));

    Entity *startButton = createEntity(Vector2D(width / 2, height/ 2 + 100), Vector2D(0.5f, 1));
    startButton->AddComponent(new Button(app->getTexture("button"), "Jugar", "toonFont", 72, [this]()
                                        { startExitTransitionTimer(pushState, new LobbyState(this->app)); }));


    addTransitioner(exitButton);
    addTransitioner(inputField);
    addTransitioner(inputLabel);
    addTransitioner(gameCodeInputField);
    addTransitioner(gameCodeInputLabel);
    addTransitioner(startButton);
    addTransitioner(lobbyTittle);
}

LoginMenuState::~LoginMenuState() {}