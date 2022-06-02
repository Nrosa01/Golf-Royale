#ifndef BALLCOLLISIONMANAGER_H
#define BALLCOLLISIONMANAGER_H

#include "../Component.h"
#include <vector>
class Transform;
class Renderer;
class Entity;
class Ball;

class BallCollisionManager : public Component
{
public:
    BallCollisionManager(std::vector<Renderer *> *obstacles);
    virtual ~BallCollisionManager();
    virtual void init();
    virtual void update(float deltaTime);
    bool checkIntersection(Renderer *ball, Renderer *obstacle, float dt);
    bool checkSideCollision(Renderer *ball, Renderer *obstacle, float dt);
    bool checkTopDownCollision(Renderer *ball, Renderer *obstacle, float dt);

private:
    Transform *transform;
    Renderer *renderer;
    Ball* ball;
    std::vector<Renderer *> *obstacles;
};

#endif