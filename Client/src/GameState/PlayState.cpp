#include "PlayState.h"
#include "../EC/Components/Renderer.h"
#include "../SDLUtils/SDLApp.h"

PlayState::PlayState(SDLApp *app) : GameState(app)
{
    Entity *bg = new Entity(app->getWidth() / 2, app->getHeight() / 2);
    bg->AddComponent(new Renderer(app->getTexture("GolfRoyaleBg")));
    gameObjects.push_back(bg);

    Entity *ball = new Entity(app->getWidth() / 4, app->getHeight() - (app->getHeight() / 15));
    //ball->AddComponent(new Renderer(app->getTexture("ball")));
    gameObjects.push_back(ball);

    Entity* enemyBall = new Entity(app->getWidth() - (app->getWidth() / 4), app->getHeight() - (app->getHeight() / 15));
    //enemyBall->AddComponent(new Renderer(app->getTexture("ball")));
    gameObjects.push_back(enemyBall);
}