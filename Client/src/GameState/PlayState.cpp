#include "PlayState.h"
#include "../EC/Entity.h"
#include "../EC/Components/Ball.h"
#include "../EC/Components/Transform.h"
#include "../EC/Components/Renderer.h"
#include "../EC/Components/BallDirection.h"
#include "../EC/Components/Transitioner.h"
#include "../EC/Components/TextRenderer.h"
#include "../EC/Components/BallCollisionManager.h"
#include "../SDLUtils/SDLApp.h"
#include <sstream>

PlayState::PlayState(SDLApp *app, std::string enemyNick, bool isMaster) : GameState(app), currentLevel(0)
{
    createEntity(Vector2D(app->getWidth() / 2, app->getHeight() / 2), Vector2D(1, 1), "menuBg");
    Entity *fg = createEntity(Vector2D(app->getWidth() / 2, app->getHeight() / 2), Vector2D(1, 1), "GolfRoyaleBg");

    Entity *ball = createEntity(Vector2D(app->getWidth() / 4, app->getHeight() - (app->getHeight() / 15)), Vector2D(1, 1), "ball");
    ball->AddComponent(new BallCollisionManager(&this->obstacles));
    ball->AddComponent(new Ball(true, isMaster));
    ball->AddComponent(new BallDirection(app->getTexture("arrow")));

    //Entity *enemyBall = createEntity(Vector2D(app->getWidth() - (app->getWidth() / 4), app->getHeight() - (app->getHeight() / 15)), Vector2D(1, 1), "ball");
    // enemyBall->AddComponent(new BallCollisionManager(&this->obstacles));
    // enemyBall->AddComponent(new Ball(false, !isMaster));

    // UI
    Entity *playerNick = addUI(Vector2D(app->getWidth() / 2 - 50, 50), Vector2D(0.15f, 0.4f), "button");
    playerNick->AddComponent(new TextRenderer(app->getPlayerName(), "toonFont", 24));

    Entity *enemyNickEnt = addUI(Vector2D(app->getWidth() / 2 + 50, 50), Vector2D(0.15f, 0.4f), "button");
    enemyNickEnt->AddComponent(new TextRenderer(enemyNick, "toonFont", 24));

    Entity *playerScore = addUI(Vector2D(app->getWidth() / 2 - 50, 80), Vector2D(0.075f, 0.2f), "button");
    playerScore->AddComponent(new TextRenderer("0", "toonFont", 16));

    Entity *enemyScore = addUI(Vector2D(app->getWidth() / 2 + 50, 80), Vector2D(0.075f, 0.2f), "button");
    enemyScore->AddComponent(new TextRenderer("0", "toonFont", 16));

    // Transitioners
    addTransitioner(fg);
    addTransitioner(ball);
    //addTransitioner(enemyBall);
    addTransitioner(playerNick);
    addTransitioner(enemyNickEnt);
    addTransitioner(playerScore);
    addTransitioner(enemyScore);

    loadLevel(currentLevel);
}

PlayState::~PlayState()
{
    deleteObstacles();
    deleteUI();
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

void PlayState::loadLevel(int level)
{
    deleteObstacles();
    std::string levelPath = "assets/levels";
    std::string levelName = "level" + std::to_string(level);

    struct obstacle
    {
        Vector2D pos;
        Vector2D scale;
    };
    std::vector<obstacle> obstacles;

    std::ifstream levelFile(levelPath + "/" + levelName + ".dat");

    if (levelFile.is_open())
    {
        std::string line;
        while (std::getline(levelFile, line))
        {
            std::stringstream ss(line);
            std::string type;
            obstacle o;
            ss >> o.pos.x >> o.pos.y >> o.scale.x >> o.scale.y;
            obstacles.push_back(o);
        }
    }
    else
    {
        std::cout << "Could not open level file: " << levelPath + "/" + levelName + ".dat" << std::endl;
    }

    int width = app->getWidth();
    for (auto &o : obstacles)
    {
        addObstacle(o.pos, o.scale, "obstacle1");
        addObstacle(o.pos + Vector2D(width / 2, 0), o.scale, "obstacle2");
    }

    for (auto &o : this->obstacles)
        o->init();
}

Entity *PlayState::addObstacle(Vector2D pos, Vector2D scale, string textureName)
{
    Entity *e = new Entity(pos.x, pos.y, app);
    e->GetTransform()->GetScale() = scale;
    Renderer *rend = new Renderer(app->getTexture(textureName));
    e->AddComponent(rend);
    obstacles.push_back(rend);

    return e;
}

Entity *PlayState::addUI(Vector2D pos, Vector2D scale, string textureName)
{
    Entity *e = new Entity(pos.x, pos.y, app);
    e->GetTransform()->GetScale() = scale;
    if (!textureName.empty())
        e->AddComponent(new Renderer(app->getTexture(textureName)));
    ui.push_back(e);

    return e;
}

void PlayState::render()
{
    GameState::render();

    for (auto &o : obstacles)
        o->render();

    for (auto &u : ui)
        u->render();
}

void PlayState::deleteObstacles()
{
    for (auto &o : obstacles)
        delete o->getOwner();
    obstacles.clear();
}

void PlayState::deleteUI()
{
    for (auto &o : ui)
        delete o;
    ui.clear();
}

void PlayState::init()
{
    GameState::init();

    for (auto &o : ui)
        o->init();
}

void PlayState::update(float dt)
{
    GameState::update(dt);

    for (auto &o : ui)
        o->update(dt);

    for (auto &o : ui)
        o->lateUpdate(dt);
}