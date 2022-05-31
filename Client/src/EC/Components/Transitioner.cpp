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

void Transitioner::lateUpdate(float deltaTime)
{
    if (isFinished)
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