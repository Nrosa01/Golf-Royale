#include "MainMenuState.h"
#include "../EC/Entity.h"
#include "../EC/Components/Renderer.h"
#include "../EC/Components/Transform.h"
#include "../SDLUtils/SDLApp.h"
#include "../EC/Components/Button.h"
#include "../EC/Components/TextField.h"
#include "../EC/Components/Transitioner.h"
#include "LoginMenuState.h"
#include <iostream>

MainMenuState::MainMenuState(SDLApp *app) : GameState(app)
{
    createEntity(Vector2D(app->getWidth() / 2, app->getHeight() / 2), Vector2D(1, 1), "menuBg");

    Entity *playButton = createEntity(Vector2D(app->getWidth() / 2, app->getHeight() / 2), Vector2D(0.5f, 1));
    playButton->addComponent(new Button(app->getTexture("button"), "Jugar", "toonFont", 72,
        [this]()
        {
            startExitTransitionTimer(pushState, new LoginMenuState(this->app));
        }));

    Entity *exitButton = createEntity(Vector2D(app->getWidth() / 2, app->getHeight() / 2 + 100), Vector2D(0.5f, 1));
    exitButton->addComponent(new Button(app->getTexture("button"), "Salir", "toonFont", 72, [this]()
                                        { startExitTransitionTimer(exitGame); }));

    Entity *title = createEntity(Vector2D(app->getWidth() / 2, app->getHeight() / 2 - 125), Vector2D(1, 1), "title");

    addTransitioner(title);
    addTransitioner(playButton);
    addTransitioner(exitButton);
}