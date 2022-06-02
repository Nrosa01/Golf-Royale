#include "PlayState.h"
#include "../EC/Entity.h"
#include "../EC/Components/Ball.h"
#include "../EC/Components/Transitioner.h"
#include "../EC/Components/TextRenderer.h"
#include "../SDLUtils/SDLApp.h"

PlayState::PlayState(SDLApp *app, std::string enemyNick, bool isMaster) : GameState(app)
{
    createEntity(Vector2D(app->getWidth() / 2, app->getHeight() / 2), Vector2D(1, 1), "menuBg");
    Entity *fg = createEntity(Vector2D(app->getWidth() / 2, app->getHeight() / 2), Vector2D(1, 1), "GolfRoyaleBg");

    Entity *ball = createEntity(Vector2D(app->getWidth() / 4, app->getHeight() - (app->getHeight() / 15)), Vector2D(1, 1), "ball");
    ball->AddComponent(new Ball(true, isMaster));

    Entity *enemyBall = createEntity(Vector2D(app->getWidth() - (app->getWidth() / 4), app->getHeight() - (app->getHeight() / 15)), Vector2D(1, 1), "ball");
    enemyBall->AddComponent(new Ball(false, !isMaster));

    // UI
    Entity *playerNick = createEntity(Vector2D(app->getWidth() / 2 - 50, 50), Vector2D(0.15f, 0.4f), "button");
    playerNick->AddComponent(new TextRenderer(app->getPlayerName(), "toonFont", 24));

    Entity *enemyNickEnt = createEntity(Vector2D(app->getWidth() / 2 + 50, 50), Vector2D(0.15f, 0.4f), "button");
    enemyNickEnt->AddComponent(new TextRenderer(enemyNick, "toonFont", 24));

    Entity *playerScore = createEntity(Vector2D(app->getWidth() / 2 - 50, 80), Vector2D(0.075f, 0.2f), "button");
    playerScore->AddComponent(new TextRenderer("0", "toonFont", 16));

    Entity *enemyScore = createEntity(Vector2D(app->getWidth() / 2 + 50, 80), Vector2D(0.075f, 0.2f), "button");
    enemyScore->AddComponent(new TextRenderer("0", "toonFont", 16));

    // Transitioners
    addTransitioner(fg);
    addTransitioner(ball);
    addTransitioner(enemyBall);
    addTransitioner(playerNick);
    addTransitioner(enemyNickEnt);
    addTransitioner(playerScore);
    addTransitioner(enemyScore);
}

void PlayState::onStateExit()
{
    NetworkMessage logout = NetworkMessage(LOGOUT);
    this->sendNetworkMessage(logout);
}

void PlayState::receiveNetworkMessage(NetworkMessage &msg)
{
    GameState::receiveNetworkMessage(msg);
    if (msg.type == PLAYER_DISCONNECTED)
        startExitTransitionTimer(popState);
}
