#include "GameState.h"
#include "../EC/Entity.h"
#include "../SDLUtils/SDLApp.h"
#include "../EC/Components/Transitioner.h"
#include "../EC/Components/Transform.h"
#include "../EC/Components/Renderer.h"
#include "../Network/NetworkMessage.h"

GameState::GameState(SDLApp *app) : app(app), startTransition(false), timer(0) {}

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

    if (startTransition)
    {
        timer += deltaTime;
        if (timer >= TRANSITION_TIME)
        {
            timer = 0;
            startTransition = false;
            if(endExitTransitionFinishCallback != nullptr)
                endExitTransitionFinishCallback(this, this->args);
        }
    }
}

void GameState::render()
{
    for (auto it = entities.begin(); it != entities.end(); ++it)
        (*it)->render();
}

void GameState::onStateEnter() 
{
    for (auto transitioner : transitioners)
        transitioner->startScale();
}

void GameState::onStateExit() {}

void GameState::receiveNetworkMessage(NetworkMessage& msg) {}

void GameState::sendNetworkMessage(NetworkMessage& msg) 
{
    this->app->sendNetworkMessage(msg);
}

void GameState::startExitTransitionTimer(GameStateCallback callback, void* args)
{
    startTransition = true;
    this->endExitTransitionFinishCallback = callback;
    this->args = args;


    for (auto transitioner : transitioners)
        transitioner->startFade();
}

void GameState::addTransitioner(Entity *e)
{
    Transitioner *transitioner = new Transitioner(TRANSITION_TIME);
    e->AddComponent(transitioner);
    transitioners.push_back(transitioner);
}

Entity* GameState::createEntity(Vector2D pos, Vector2D scale, string textureName)
{
    Entity *e = new Entity(pos.x, pos.y, app);
    e->GetTransform()->GetScale() = scale;
    if (!textureName.empty())
        e->AddComponent(new Renderer(app->getTexture(textureName)));
    entities.push_back(e);

    return e;
}

SDLApp* GameState::getApp()
{
    return app;
}