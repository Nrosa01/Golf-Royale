#include "Transitioner.h"
#include "Transform.h"
#include "../Entity.h"
#include "../../MathUtils/LerpingFunctions.h"

using namespace MathUtils;

Transitioner::Transitioner(float duration) : Component(typeid(Transitioner).name())
{
    this->duration = duration;
    timer = 0.0f;
    isFinished = false;
    isScaling = true;
    disabled = false;
}

Transitioner::~Transitioner() {}

void Transitioner::init()
{
    transform = &this->ent->transform;;
    initialScale = transform->getScale();
}

void Transitioner::lateUpdate(float deltaTime)
{
    if (isFinished || disabled)
        return;

    timer += deltaTime;

    if (timer > duration)
    {
        timer = duration;
        isFinished = true;
    }

    float lerpTime = timer / duration;
    if (!isScaling)
        lerpTime = 1 - lerpTime;

    float scaleX = lerp(0, initialScale.x, lerpTime);
    float scaleY = lerp(0, initialScale.y, lerpTime);
    transform->getScale() = Vector2D(scaleX, scaleY);
}

void Transitioner::startScale()
{
    if (disabled)
        return;
    isScaling = true;
    timer = 0.0f;
    isFinished = false;
    transform->getScale() = Vector2D(0, 0);
}

void Transitioner::startFade()
{
    if (disabled)
        return;
    isScaling = false;
    timer = 0.0f;
    isFinished = false;
    transform->getScale() = initialScale;
}

void Transitioner::stop()
{
    isFinished = true;
}

void Transitioner::disable()
{
    disabled = true;
}

void Transitioner::enable()
{
    disabled = false;
}