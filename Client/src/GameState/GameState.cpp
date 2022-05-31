#include "GameState.h"
#include "../EC/Entity.h"
#include "../SDLUtils/SDLApp.h"

GameState::GameState(SDLApp *app) : app(app) {}

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

    for (auto it = entities.begin(); it != entities.end(); ++it)
        (*it)->lateUpdate(deltaTime);
}

void GameState::render()
{
    for (auto it = entities.begin(); it != entities.end(); ++it)
        (*it)->render();
}
