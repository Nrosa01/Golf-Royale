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
class Renderer;
class Texture;

class Ball : public Component
{
public:
    Ball(bool main = true);
    virtual ~Ball();
    virtual void init();
    virtual void update(float deltaTime);
    bool isOutOfBoundsX(float deltaTime);
    bool isOutOfBoundsY(float deltaTime);
    float getDistance(Vector2D startPoint, Vector2D endPoint);
    void setVelocity(Vector2D startPoint, Vector2D endPoint);
    void handleBallScale();
private:
Vector2D velocity;
Vector2D startPressPoint;
Transform* transform;
Renderer* renderer;
float friction;
float maxSpeed = 30.0f;
bool mainBall;
BallState state;
float mininumThreshold;
};

#endif