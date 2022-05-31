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
                                        { startTransitionTimer(); }));
    this->entities.push_back(playButton);
    playButton->GetTransform()->GetScale() = Vector2D(0.5f, 1.0f);

    Entity *exitButton = new Entity(app->getWidth() / 2, app->getHeight() / 2 + 100, app);
    exitButton->AddComponent(new Button(app->getTexture("button"), "Salir", "toonFont", 72, [app]()
                                        { app->quit(); }));
    this->entities.push_back(exitButton);
    exitButton->GetTransform()->GetScale() = Vector2D(0.5f, 1.0f);

    Entity *title = new Entity(app->getWidth() / 2, app->getHeight() / 2 - 125, app);
    title->AddComponent(new Renderer(app->getTexture("title")));
    this->entities.push_back(title);
    title->GetTransform()->GetScale() = Vector2D(1.15f, 1.15f);

    Transitioner *transitioner = new Transitioner(TRANSITION_TIME);
    playButton->AddComponent(transitioner);
    this->transitioners.push_back(transitioner);

    title->AddComponent(transitioner = new Transitioner(TRANSITION_TIME));
    this->transitioners.push_back(transitioner);

    exitButton->AddComponent(transitioner = new Transitioner(TRANSITION_TIME));
    this->transitioners.push_back(transitioner);
}

void MainMenuState::update(float deltaTime)
{
    GameState::update(deltaTime);

    if (startTransition)
    {
        timer += deltaTime;
        if (timer >= TRANSITION_TIME)
        {
            timer = 0;
            startTransition = false;
            app->pushState(new LobbyState(app));
        }
    }
}

void MainMenuState::startTransitionTimer()
{
    startTransition = true;

    for (auto transitioner : transitioners)
        transitioner->startFade();
}