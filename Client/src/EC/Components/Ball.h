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
    Ball(bool main, bool playerTurn);
    virtual ~Ball();
    virtual void init();
    virtual void update(float deltaTime);
    virtual void receiveNetworkMessage(NetworkMessage *msg);
    float getDistance(Vector2D startPoint, Vector2D endPoint);
    float getLaunchStrength(Vector2D startPoint, Vector2D endPoint);
    void setVelocity(Vector2D startPoint, Vector2D endPoint);
    void setVelocity(Vector2D velocity);
    Vector2D getVelocity() const;
    void handleMain();

    float getCurrentLaunchForce() const;
    Vector2D getCurrentLaunchDirection() const;
    float getMaxLaunchForce() const;
    float getMininumThreshold() const;

    void sideCollision();
    void topDownCollision();

    bool isMainBall() const;

private:
    Vector2D velocity;
    Vector2D startPressPoint;
    Renderer *renderer;
    float friction;
    float maxLaunchForce; // Magnitud maxima
    bool mainBall;
    BallState state;
    float mininumThreshold;
    float sensibilidad; // Multiplica la potencia del movimiento
    bool playerTurn;

    float currentLaunchForce;
    Vector2D currentLaunchDirection;
};

#endif