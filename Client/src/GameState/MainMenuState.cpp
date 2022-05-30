#include "MainMenuState.h"
#include "../EC/Components/Renderer.h"
#include "../SDLUtils/SDLApp.h"

MainMenuState::MainMenuState(SDLApp* app) : GameState(app)
{
    Entity* bg = new Entity();
    //bg->AddComponent(new Renderer(app->getTexture("menuBg")));
    gameObjects.push_back(bg);
}