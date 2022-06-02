#ifndef PLAYSTATE_H
#define PLAYSTATE_H

#include "GameState.h"
#include <vector>
class Entity;
class Renderer;

class PlayState : public GameState
{
public:
    PlayState(SDLApp *app, std::string enemyNick = "", bool isMaster = true);
    virtual ~PlayState();
    virtual void init();
    virtual void update(float dt);
    virtual void render();
    virtual void receiveNetworkMessage(NetworkMessage &msg);
    virtual void onStateExit();
    void deleteObstacles();
    void deleteUI();

private:
    int currentLevel;
    std::vector<Renderer *> obstacles;
    std::vector<Entity *> ui;
    void loadLevel(int level);
    Entity *addObstacle(Vector2D pos, Vector2D scale, string textureName);
    Entity *addUI(Vector2D pos, Vector2D scale, string textureName);
};

#endif