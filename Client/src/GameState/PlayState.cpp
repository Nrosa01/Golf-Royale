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

PlayState::PlayState(SDLApp *app, std::string enemyNick, bool isMaster, uint8_t playerScore, uint8_t enemyScore, uint8_t currentLevel) : GameState(app)
{
    this->currentLevel = currentLevel;
    this->enemyNick = enemyNick;
    this->playerScore = playerScore;
    this->enemyScore = enemyScore;
    waitingForLevel = false;

    createEntity(Vector2D(app->getWidth() / 2, app->getHeight() / 2), Vector2D(1, 1), "menuBg");
    Entity *fg = createEntity(Vector2D(app->getWidth() / 2, app->getHeight() / 2), Vector2D(1, 1), "GolfRoyaleBg");

    Entity *ball = createEntity(Vector2D(app->getWidth() / 2, app->getHeight() - (app->getHeight() / 15)), Vector2D(1, 1), "ball");
    ball->AddComponent(new Ball(true, isMaster));
    ball->AddComponent(new BallDirection(app->getTexture("arrow")));
    ball->AddComponent(player = new BallCollisionManager(&this->obstacles));

    Entity *enemyBall = createEntity(Vector2D(app->getWidth() / 2, app->getHeight() - (app->getHeight() / 15)), Vector2D(1, 1), "ballEnemy");
    enemyBall->AddComponent(new BallCollisionManager(&this->obstacles));
    enemyBall->AddComponent(new Ball(false, true));

    // UI
    Entity *playerNick = addUI(Vector2D(app->getWidth() / 2 - 50, 50), Vector2D(0.15f, 0.4f), "button");
    playerNick->AddComponent(new TextRenderer(app->getPlayerName(), "toonFont", 24));

    Entity *enemyNickEnt = addUI(Vector2D(app->getWidth() / 2 + 50, 50), Vector2D(0.15f, 0.4f), "button");
    enemyNickEnt->AddComponent(new TextRenderer(enemyNick, "toonFont", 24));

    Entity *playerScoreUI = addUI(Vector2D(app->getWidth() / 2 - 50, 80), Vector2D(0.075f, 0.2f), "button");
    playerScoreUI->AddComponent(new TextRenderer(std::to_string(playerScore), "toonFont", 16));

    Entity *enemyScoreUI = addUI(Vector2D(app->getWidth() / 2 + 50, 80), Vector2D(0.075f, 0.2f), "button");
    enemyScoreUI->AddComponent(new TextRenderer(std::to_string(enemyScore), "toonFont", 16));

    // Transitioners
    fgTransitioner = addTransitioner(fg);
    addTransitioner(ball);
    addTransitioner(enemyBall);
    addTransitioner(playerNick);
    addTransitioner(enemyNickEnt);
    addTransitioner(playerScoreUI);
    addTransitioner(enemyScoreUI);

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
    {
        fgTransitioner->enable();
        startExitTransitionTimer(popState);
    }
    else if (msg.type == LEVEL_END)
    {
        PlayState *nextState = new PlayState(app, enemyNick, false, playerScore, enemyScore + 1, currentLevel + 1);
        startExitTransitionTimer(changeState, nextState);
        app->playAudio("hole");
        fgTransitioner->disable();
    }
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
        // First line is the goal
        std::string goal;
        if (std::getline(levelFile, goal))
        {
            std::stringstream ss(goal);
            std::string type;
            obstacle o;
            ss >> o.pos.x >> o.pos.y >> o.scale.x >> o.scale.y;
            this->hole = createEntity(o.pos, o.scale, "hole");
            addTransitioner(hole);
        }

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

    for (auto &o : obstacles)
        addObstacle(o.pos, o.scale, "obstacle");
}

Entity *PlayState::addObstacle(Vector2D pos, Vector2D scale, string textureName)
{
    Entity *e = new Entity(pos.x, pos.y, app);
    e->GetTransform()->GetScale() = scale;
    Renderer *rend = new Renderer(app->getTexture(textureName));
    e->AddComponent(rend);
    obstacles.push_back(rend);
    entities.push_back(e);

    addTransitioner(e);

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

    for (auto &u : ui)
        u->render();
}

void PlayState::deleteObstacles()
{
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

    if (currentLevel > 0)
        fgTransitioner->disable();
}

void PlayState::update(float dt)
{
    GameState::update(dt);

    for (auto &o : ui)
        o->update(dt);

    for (auto &o : ui)
        o->lateUpdate(dt);

    updateGameState();
}

bool PlayState::checkPlayerInHole()
{
    return player->checkIntersection(hole);
}

void PlayState::updateGameState()
{
    if (waitingForLevel)
        return;

    if (checkPlayerInHole())
    {
        PlayState *nextState = new PlayState(app, enemyNick, true, playerScore + 1, enemyScore, currentLevel + 1);
        NetworkMessage msg(LEVEL_END);
        this->sendNetworkMessage(msg);
        startExitTransitionTimer(changeState, nextState);
        waitingForLevel = true;
        app->playAudio("hole");
        fgTransitioner->disable();
    }
}
