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

MainMenuState::MainMenuState(SDLApp *app) : GameState(app), startTransition(false), timer(0)
{
    Entity *bg = new Entity(app->getWidth() / 2, app->getHeight() / 2, app);
    bg->AddComponent(new Renderer(app->getTexture("menuBg")));
    this->entities.push_back(bg);

    Entity *playButton = new Entity(app->getWidth() / 2, app->getHeight() / 2, app);
    playButton->AddComponent(new Button(app->getTexture("button"), "Jugar", "toonFont", 72, [this]()
                                        { startTransition = true;}));
    playButton->AddComponent(new Transitioner(TRANSITION_TIME));
    this->entities.push_back(playButton);
    playButton->GetTransform()->GetScale() = Vector2D(0.5f, 1.0f);

    Entity *exitButton = new Entity(app->getWidth() / 2, app->getHeight() / 2 + 100, app);
    exitButton->AddComponent(new Button(app->getTexture("button"), "Salir", "toonFont", 72, [app]()
                                        { app->quit(); }));
    exitButton->AddComponent(new Transitioner(TRANSITION_TIME));
    this->entities.push_back(exitButton);
    exitButton->GetTransform()->GetScale() = Vector2D(0.5f, 1.0f);

    Entity *title = new Entity(app->getWidth() / 2, app->getHeight() / 2 - 125, app);
    title->AddComponent(new Renderer(app->getTexture("title")));
    title->AddComponent(new Transitioner(TRANSITION_TIME));
    this->entities.push_back(title);
    title->GetTransform()->GetScale() = Vector2D(1.15f, 1.15f);
}

void MainMenuState::update(float deltaTime)
{
    GameState::update(deltaTime);

    if(startTransition)
    {
        timer += deltaTime;
        if(timer >= TRANSITION_TIME)
        {
            timer = 0;
            startTransition = false;
            game->pushState(new LobbyState(game)); 
        }
    }
}