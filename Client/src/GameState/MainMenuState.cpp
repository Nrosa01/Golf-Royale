#include "MainMenuState.h"
#include "../EC/Entity.h"
#include "../EC/Components/Renderer.h"
#include "../EC/Components/Transform.h"
#include "../SDLUtils/SDLApp.h"
#include "../EC/Components/Button.h"
#include "../EC/Components/TextField.h"
#include "../EC/Components/Transitioner.h"
#include "LobbyState.h"
#include <iostream>

MainMenuState::MainMenuState(SDLApp *app) : GameState(app)
{
    createEntity(Vector2D(app->getWidth() / 2, app->getHeight() / 2), Vector2D(1, 1), "menuBg");

    Entity *playButton = createEntity(Vector2D(app->getWidth() / 2, app->getHeight() / 2), Vector2D(0.5f, 1));
    playButton->AddComponent(new Button(app->getTexture("button"), "Jugar", "toonFont", 72, [this]()
                                        { startExitTransitionTimer(); }));

    Entity *exitButton = createEntity(Vector2D(app->getWidth() / 2, app->getHeight() / 2 + 100), Vector2D(0.5f, 1));
    exitButton->AddComponent(new Button(app->getTexture("button"), "Salir", "toonFont", 72, [app]()
                                        { app->quit(); }));

    Entity *title = createEntity(Vector2D(app->getWidth() / 2, app->getHeight() / 2 - 125), Vector2D(1, 1));
    title->AddComponent(new Renderer(app->getTexture("title")));

    addTransitioner(playButton);
    addTransitioner(exitButton);
}

void MainMenuState::onStateExit()
{
    app->pushState(new LobbyState(app));
}