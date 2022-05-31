#include "Transitioner.h"
#include "Transform.h"
#include "../Entity.h"
#include "../../MathUtils/LerpingFunctions.h"

using namespace MathUtils;

Transitioner::Transitioner(float duration) : Component("Transitioner")
{
    this->duration = duration;
    timer = 0.0f;
    isFinished = false;
    isScaling = true;
}

Transitioner::~Transitioner() {}

void Transitioner::init()
{
    transform = this->ent->GetTransform();
    initialScale = transform->GetScale();
}

void Transitioner::update(float deltaTime)
{
    if (isFinished)
        return;

    if (isScaling)
        timer += deltaTime;
    else
        timer -= deltaTime;

    if (timer > duration)
    {
        timer = duration;
        isFinished = true;
    }
    else if(timer < 0.0f)
    {
        timer = 0.0f;
        isFinished = true;
    }

    if (isScaling)
    {
        float scaleX = Lerp(0, initialScale.x, timer / duration);
        float scaleY = Lerp(0, initialScale.y, timer / duration);
        transform->GetScale() = Vector2D(scaleX, scaleY);
    }
    else
    {
        float scaleX = Lerp(initialScale.x, 0, timer / duration);
        float scaleY = Lerp(initialScale.y, 0, timer / duration);
        transform->GetScale() = Vector2D(scaleX, scaleY);
    }
}


void Transitioner::startScale()
{
    isScaling = true;
    timer = 0.0f;
    isFinished = false;
}

void Transitioner::startFade()
{
    isScaling = false;
    timer = duration;
    isFinished = false;
}