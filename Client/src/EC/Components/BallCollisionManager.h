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
    bool checkIntersection(Entity *obstacle);

private:
    bool checkIntersection(Renderer *ball, Renderer *obstacle);
    Vector2D getCollisionNormal(Renderer *ball, Renderer *obstacle, Vector2D ballVelocity);
    void takeBodyOutOfCollision(Renderer *ball, Renderer *obstacle, Vector2D collisionNormal);
    void notifyCollision(Vector2D collisionNormal);
    Vector2D makeUnitary(Vector2D vector);
    Renderer *renderer;
    Ball *ball;
    std::vector<Renderer *> *obstacles;
    bool main;
};

#endif