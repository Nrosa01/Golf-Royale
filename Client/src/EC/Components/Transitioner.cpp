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
    adjusted = false;
    disabled = false;
}

Transitioner::~Transitioner() {}

void Transitioner::init()
{
    transform = this->ent->GetTransform();
    initialScale = transform->GetScale();
}

void Transitioner::lateUpdate(float deltaTime)
{
    if (!adjusted)
    {
        adjusted = true;
        if (isScaling)
            transform->GetScale() = initialScale;
        else
            transform->GetScale() = Vector2D(0, 0);
    }

    if (isFinished || disabled)
        return;

    timer += deltaTime;

    if (timer > duration)
    {
        timer = duration;
        isFinished = true;
        adjusted = true;
    }

    float lerpTime = timer / duration;
    if (!isScaling)
        lerpTime = 1 - lerpTime;

    float scaleX = Lerp(0, initialScale.x, lerpTime);
    float scaleY = Lerp(0, initialScale.y, lerpTime);
    transform->GetScale() = Vector2D(scaleX, scaleY);
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
    timer = 0.0f;
    isFinished = false;
}

void Transitioner::stop()
{
    if (transform != nullptr)
        transform->GetScale() = initialScale;
    isFinished = true;
    adjusted = false;
}

void Transitioner::disable()
{
    disabled = true;
}

void Transitioner::enable()
{
    disabled = false;
}