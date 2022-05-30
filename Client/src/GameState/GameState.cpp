#include "GameState.h"
#include "../EC/Entity.h"
#include "../EC/EventHandler.h"
#include "../SDLUtils/SDLApp.h"

GameState::GameState(SDLApp* app) : game(app){ }

GameState::~GameState()
{
    for (auto it = entities.begin(); it != entities.end(); it++)
        delete *it;
    entities.clear();
}

void GameState::update(float deltaTime)
{
    for (auto it = entities.begin(); it != entities.end(); ++it)
        (*it)->update(deltaTime);
}

void GameState::render()
{
    for (auto it = entities.begin(); it != entities.end(); ++it)
        (*it)->render();
}

void GameState::handleEvent(SDL_Event& e)
{
    for (auto it = eventHandlers.begin(); it != eventHandlers.end(); ++it)
        (*it)->handleEvent(e);
}
