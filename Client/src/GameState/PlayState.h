#ifndef PLAYSTATE_H
#define PLAYSTATE_H

#include "GameState.h"
#include <vector>
class Entity;
class Renderer;
class BallCollisionManager;
class Transitioner;
#define LAST_LEVEL 5

class PlayState : public GameState
{
public:
    PlayState(SDLApp *app, std::string enemyNick = "", bool isMaster = true, uint8_t playerScore = 0, uint8_t enemyScore = 0, uint8_t currentLevel = 0);
    virtual ~PlayState();
    virtual void init();
    virtual void update(float dt);
    virtual void render();
    virtual void receiveNetworkMessage(NetworkMessage &msg);
    virtual void onStateExit();
    void deleteUI();
    bool checkPlayerInHole();
    void updateGameState();

private:
    Transitioner *fgTransitioner;
    BallCollisionManager *player;
    Entity *hole;
    uint8_t playerScore;
    uint8_t enemyScore;
    std::string enemyNick;
    int currentLevel;
    std::vector<Renderer *> obstacles;
    std::vector<Entity *> ui;
    void loadLevel(int level);
    Entity *addObstacle(Vector2D pos, Vector2D scale, string textureName);
    Entity *addUI(Vector2D pos, Vector2D scale, string textureName);
    bool waitingForLevel;
};

#endif