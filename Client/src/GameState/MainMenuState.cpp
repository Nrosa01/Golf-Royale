#include "MainMenuState.h"
#include "../EC/Entity.h"
#include "../EC/Components/Renderer.h"
#include "../EC/Components/Transform.h"
#include "../SDLUtils/SDLApp.h"
#include "../EC/Components/Button.h"
#include <iostream>

MainMenuState::MainMenuState(SDLApp *app) : GameState(app)
{
    Entity *bg = new Entity(app->getWidth() / 2, app->getHeight() / 2, app);
    bg->AddComponent(new Renderer(app->getTexture("menuBg")));
    this->entities.push_back(bg);

    Entity *playButton = new Entity(app->getWidth() / 2, app->getHeight() / 2, app);
    playButton->AddComponent(new Button(app->getTexture("button"), "Jugar", "toonFont_72", []() {
        //this->app->setState("GameState");
        std::cout << "Jugar" << std::endl;
    }));
    this->entities.push_back(playButton);
    playButton->GetTransform()->GetScale() = Vector2D(0.75f, 1.0f);

    Entity *exitButton = new Entity(app->getWidth() / 2, app->getHeight() / 2 + 100, app);
    exitButton->AddComponent(new Button(app->getTexture("button"), "Salir", "toonFont_72", [app]() {
        app->quit();
    }));
    this->entities.push_back(exitButton);
    exitButton->GetTransform()->GetScale() = Vector2D(0.75f, 1.0f);

    Entity *title = new Entity(app->getWidth() / 2, app->getHeight() / 2 - 125, app);
    title->AddComponent(new Renderer(app->getTexture("title")));
    this->entities.push_back(title);
    title->GetTransform()->GetScale() = Vector2D(1.15f, 1.15f);
}