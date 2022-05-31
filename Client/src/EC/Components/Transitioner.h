#ifndef TRANSITIONER_H
#define TRANSITIONER_H

#include "../Component.h"
#include "../../MathUtils/Vector2D.h"

class Transform;

class Transitioner : public Component
{
public:
    Transitioner(float duration);
    virtual ~Transitioner();
    virtual void init();
    virtual void update(float deltaTime);
    void startScale();
    void startFade();

private:
    Transform *transform;
    float duration;
    float timer;
    Vector2D initialScale;
    bool isFinished;
    bool isScaling;
};

#endif