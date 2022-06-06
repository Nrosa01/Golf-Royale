#include "BallDirection.h"
#include "../Entity.h"
#include "Transform.h"
#include "Ball.h"
#include "../../SDLUtils/Texture.h"
#include "../../SDLUtils/SDLApp.h"
#include <SDL2/SDL.h>

BallDirection::BallDirection(Texture *texture) : Component(typeid(BallDirection).name()), texture(texture), ball(nullptr){};

BallDirection::~BallDirection()
{
}

void BallDirection::init()
{
    ball = this->ent->getComponent<Ball>();
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
    SDL_RenderDrawLine(this->ent->getGame()->getRenderer(), transform->getPosition().getX(), transform->getPosition().getY(), transform->getPosition().getX() + dir.getX() * lineDistance, transform->getPosition().getY() + dir.getY() * lineDistance);

    SDL_Rect destRect;
    int textW = texture->getW() * transform->getScale().x;
    int textH = texture->getH() * transform->getScale().y;
    SDL_Point bottomCenter = {textW / 2, textH}; // Pivotar en la parte baja de la flecha

    destRect.x = transform->getPosition().getX() - bottomCenter.x;
    destRect.y = transform->getPosition().getY() - bottomCenter.y;
    destRect.w = textW;
    destRect.h = textH;

    texture->render(destRect, angle, bottomCenter);
}