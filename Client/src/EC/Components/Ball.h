#ifndef BALLCOMPONENT_H
#define BALLCOMPONENT_H

enum class BallState
{
    PRESSED,
    MOVING,
    IDLE
};

#include "../Component.h"
#include "../../MathUtils/Vector2D.h"
class Transform;

class Ball : public Component
{
public:
    Ball(bool main = true);
    virtual ~Ball();
    virtual void init();
    virtual void update(float deltaTime);
    bool isOutOfBoundsX();
    bool isOutOfBoundsY();
    float getDistance(Vector2D startPoint, Vector2D endPoint);
    void setVelocity(Vector2D startPoint, Vector2D endPoint);
private:
Vector2D velocity;
Vector2D startPressPoint;
Transform* transform;
float friction = 0.001f;
bool mainBall;
BallState state;
};

#endif