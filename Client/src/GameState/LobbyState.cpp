#include "LobbyState.h"
#include "../EC/Entity.h"
#include "../EC/Components/Renderer.h"
#include "../EC/Components/Transform.h"
#include "../SDLUtils/SDLApp.h"
#include "../EC/Components/Button.h"
#include "../EC/Components/TextField.h"
#include "../EC/Components/Transitioner.h"
#include "MainMenuState.h"
#include <iostream>

LobbyState::LobbyState(SDLApp *app) : GameState(app)
{
    createEntity(Vector2D(app->getWidth() / 2, app->getHeight() / 2), Vector2D(1, 1), "menuBg");

    Entity *exitButton = createEntity(Vector2D(app->getWidth() / 2, app->getHeight() / 2 + 100), Vector2D(0.5f, 1));
    exitButton->AddComponent(new Button(app->getTexture("button"), "Menu", "toonFont", 72, [this]()
                                        { startExitTransitionTimer(); }));


    addTransitioner(exitButton);
}

LobbyState::~LobbyState() {}

void LobbyState::onStateExit()
{
    app->popState();
}