#include "PlayState.h"
#include "../EC/Entity.h"
#include "../EC/Components/Renderer.h"
#include "../EC/Components/Ball.h"
#include "../SDLUtils/SDLApp.h"

#include "../Network/Client.h"

PlayState::PlayState(SDLApp *app) : GameState(app)
{
    Entity *bg = new Entity(app->getWidth() / 2, app->getHeight() / 2, app);
    bg->AddComponent(new Renderer(app->getTexture("GolfRoyaleBg")));
    this->entities.push_back(bg);

    Entity *ball = new Entity(app->getWidth() / 4, app->getHeight() - (app->getHeight() / 15), app);
    ball->AddComponent(new Ball(true));
    ball->AddComponent(new Renderer(app->getTexture("ball")));
    this->entities.push_back(ball);

    Entity* enemyBall = new Entity(app->getWidth() - (app->getWidth() / 4), app->getHeight() - (app->getHeight() / 15), app);
    enemyBall->AddComponent(new Renderer(app->getTexture("ball")));
    enemyBall->AddComponent(new Ball(false));
    this->entities.push_back(enemyBall);

    Client* client = new Client("0.0.0.0", "13000");
    //client->login();
    //client->logout();
    client->test();
    client->test();
    delete client;
}