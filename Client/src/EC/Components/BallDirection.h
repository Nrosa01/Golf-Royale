#ifndef BALLDIRECTION_H
#define BALLDIRECTION_H

#include "../Component.h"

class Texture;
class Transform;
class Ball;

class BallDirection : public Component
{
public:
    BallDirection(Texture *texture);
    virtual ~BallDirection();
    virtual void init();
    virtual void render();

private:
    Texture *texture;
    Ball* ball;
    float maxLineDistance;
};

#endif