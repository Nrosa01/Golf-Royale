#include "MainMenuState.h"
#include "../EC/Entity.h"
#include "../EC/Components/Renderer.h"
#include "../SDLUtils/SDLApp.h"

MainMenuState::MainMenuState(SDLApp* app) : GameState(app)
{
    Entity* bg = new Entity(app);
    bg->AddComponent(new Renderer(app->getTexture("menuBg")));
    this->entities.push_back(bg);
}