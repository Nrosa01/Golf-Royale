#include "LobbyState.h"
#include "../EC/Entity.h"
#include "../EC/Components/Renderer.h"
#include "../EC/Components/Ball.h"
#include "../SDLUtils/SDLApp.h"

LobbyState::LobbyState(SDLApp *app) : GameState(app)
{
    Entity *bg = new Entity(app->getWidth() / 2, app->getHeight() / 2, app);
    bg->AddComponent(new Renderer(app->getTexture("menuBg")));
    this->entities.push_back(bg);
}

LobbyState::~LobbyState(){}