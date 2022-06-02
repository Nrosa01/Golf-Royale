#include "BallDirection.h"
#include "../Entity.h"
#include "Transform.h"
#include "Ball.h"
#include "../../SDLUtils/Texture.h"
#include "../../SDLUtils/SDLApp.h"
#include <SDL2/SDL.h>

BallDirection::BallDirection(Texture *texture) : Component(typeid(BallDirection).name()), transform(nullptr), texture(texture), ball(nullptr){};

BallDirection::~BallDirection()
{
}

void BallDirection::init()
{
    transform = this->ent->GetTransform();
    ball = this->ent->GetComponent<Ball>();
    maxLineDistance = 10;

    if (transform == nullptr)
    {
        std::cout << "BallDirection::init() - ERROR: Entity does not have a Transform component!" << std::endl;
        return;
    }

    if (ball == nullptr)
    {
        std::cout << "BallDirection::init() - ERROR: Entity does not have a Ball component!" << std::endl;
        return;
    }
}

void BallDirection::render()
{
    float currentLaunchForce = ball->getCurrentLaunchForce();
    if (currentLaunchForce <= 0)
        return;
    Vector2D dir = ball->getCurrentLaunchDirection();
    float angle = dir.angle() + 90;
    float lineDistance = currentLaunchForce / maxLineDistance;

    // Dibujar una linea en la direccion dir
    SDL_RenderDrawLine(this->ent->GetGame()->getRenderer(), transform->GetPosition().getX(), transform->GetPosition().getY(), transform->GetPosition().getX() + dir.getX() * lineDistance, transform->GetPosition().getY() + dir.getY() * lineDistance);

    SDL_Rect destRect;
    int textW = texture->getW() * transform->GetScale().x;
    int textH = texture->getH() * transform->GetScale().y;
    SDL_Point bottomCenter = {textW / 2, textH}; // Pivotar en la parte baja de la flecha

    destRect.x = transform->GetPosition().getX() - bottomCenter.x;
    destRect.y = transform->GetPosition().getY() - bottomCenter.y;
    destRect.w = textW;
    destRect.h = textH;

    texture->render(destRect, angle, bottomCenter);
}