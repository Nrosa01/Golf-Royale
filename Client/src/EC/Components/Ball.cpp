#include "Ball.h"
#include "Transform.h"
#include "../Entity.h"
#include "../../SDLUtils/SDLApp.h"
#include <iostream>

Ball::Ball(bool main) : Component("Ball")
{
    state = BallState::IDLE;
    this->mainBall = main;
}

Ball::~Ball() {}

void Ball::init()
{
    transform = this->ent->GetTransform();
    velocity = Vector2D(10, 20);
}

void Ball::update(float deltaTime)
{
    std::cout << "Velocity x: " << velocity.getX() << " y: " << velocity.getY() << std::endl;

    if (Input()->IsMouseButtonDown(0) && state == BallState::IDLE)
    {
        state = BallState::PRESSED;
        startPressPoint = Input()->GetMousePosition();
        std::cout << "startPressPoint: " << startPressPoint.x << " " << startPressPoint.y << std::endl;
    }

    if (!Input()->IsMouseButtonDown(0) && state == BallState::PRESSED)
    {
        state = BallState::MOVING;
        setVelocity(startPressPoint, Input()->GetMousePosition());
        std::cout << "endPressPoint: " << Input()->GetMousePosition().x << " " << Input()->GetMousePosition().y << std::endl;
        std::cout << "setVelocity: " << velocity.x << " " << velocity.y << std::endl;
    }

    if (isOutOfBoundsX())
        velocity.x = -velocity.x;
    if (isOutOfBoundsY())
        velocity.y = -velocity.y;

    // Update position
    transform->GetPosition().x += velocity.x * deltaTime;
    transform->GetPosition().y += velocity.y * deltaTime;

    // Simulate friction
    if (velocity.Magnitude() > 0.01f)
    {
        velocity.x -= friction * deltaTime;
        velocity.y -= friction * deltaTime;
    }
    else
    {
        velocity.x = 0.0f;
        velocity.y = 0.0f;
        state == BallState::IDLE;
    }
}

bool Ball::isOutOfBoundsX()
{
    int screenWidth = this->ent->GetGame()->getWidth();

    // If we are mainBall, we are retriscted to the left half of the screen
    if (mainBall)
        return transform->GetPosition().x > screenWidth / 2 || transform->GetPosition().x < 0;
    else
        return transform->GetPosition().x < screenWidth / 2 || transform->GetPosition().x > screenWidth;
}

bool Ball::isOutOfBoundsY()
{
    int screenHeight = this->ent->GetGame()->getHeight();

    return transform->GetPosition().y > screenHeight || transform->GetPosition().y < 0;
}

float Ball::getDistance(Vector2D startPoint, Vector2D endPoint)
{
    return SDL_sqrt(SDL_pow(endPoint.x - startPoint.x, 2) + SDL_pow(endPoint.y - startPoint.y, 2));
}

void Ball::setVelocity(Vector2D startPoint, Vector2D endPoint)
{
    float distance = getDistance(startPoint, endPoint);
    Vector2D dir = (endPoint - startPoint).Normalized();
    dir *= (int)distance;
    velocity = dir;
}