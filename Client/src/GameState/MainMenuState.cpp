#include "MainMenuState.h"
#include "../EC/Entity.h"
#include "../EC/Components/Renderer.h"
#include "../SDLUtils/SDLApp.h"

MainMenuState::MainMenuState(SDLApp *app) : GameState(app)
{
    Entity *bg = new Entity(app->getWidth() / 2, app->getHeight() / 2, app);
    bg->AddComponent(new Renderer(app->getTexture("menuBg")));
    this->entities.push_back(bg);
}

void MainMenuState::render()
{
    GameState::render();
    this->game->renderTextCenter(0, -125, "Golf Royale", "toonFont_120", {255, 255, 255});
    this->game->renderTextCenter(0, 0, "Jugar", "toonFont_84", {255, 255, 255});
    this->game->renderTextCenter(0, 100, "Controles", "toonFont_84", {255, 255, 255});
}