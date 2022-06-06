#include "Ball.h"
#include "Transform.h"
#include "Renderer.h"
#include "../Entity.h"
#include "../../SDLUtils/SDLApp.h"
#include <iostream>

Ball::Ball(bool main, bool playerTurn) : Component(typeid(Ball).name())
{
    state = BallState::IDLE;
    this->mainBall = main;
    friction = 1000.0f;
    maxLaunchForce = 2000.0f;
    mininumThreshold = 1.5f;
    this->playerTurn = playerTurn;

    currentLaunchForce = 0;
    currentLaunchDirection = Vector2D(0, 0);
}

Ball::~Ball() {}

void Ball::init()
{
    transform = this->ent->getTransform();
    renderer = this->ent->getComponent<Renderer>();
    sensibilidad = 10.0f;
}

void Ball::update(float deltaTime)
{
    handleMain();

    if (state != BallState::MOVING)
        return;

    if (mainBall)
    {
        BallPosMessage hitMsg(transform->getPosition().x, transform->getPosition().y);
        sendNetworkMessage(hitMsg);
    }

    // Update position
    transform->getPosition().x += velocity.x * deltaTime;
    transform->getPosition().y += velocity.y * deltaTime;

    // Simulate friction
    if (velocity.magnitude() > mininumThreshold)
    {
        float vel = velocity.magnitude() - (friction * deltaTime);
        vel = vel < mininumThreshold ? 0 : vel;
        velocity = velocity.normalized() * vel;
    }
    else
    {
        velocity.x = 0.0f;
        velocity.y = 0.0f;
        state = BallState::IDLE;

        if (!mainBall)
            return;
        playerTurn = false;
        NetworkMessage msg(TURN_END);
        sendNetworkMessage(msg);
    }

    // handleBallScale();
}

void Ball::handleMain()
{
    if (!this->mainBall || !playerTurn)
        return;

    Vector2D mousePos = Input()->getMousePosition();

    if (Input()->isMouseButtonDown(0) && state == BallState::IDLE)
    {
        state = BallState::PRESSED;
        startPressPoint = mousePos;
        // std::cout << "startPressPoint: " << startPressPoint.x << " " << startPressPoint.y << std::endl;
    }

    if (state == BallState::PRESSED)
    {
        currentLaunchForce = getLaunchStrength(startPressPoint, mousePos);
        currentLaunchDirection = (startPressPoint - mousePos).normalized();
    }

    if (!Input()->isMouseButtonDown(0) && state == BallState::PRESSED)
    {
        state = BallState::MOVING;
        setVelocity(startPressPoint, mousePos);
        currentLaunchForce = 0;

        if (velocity.magnitude() > mininumThreshold)
        {
            this->playSound("swing");
        }
        // std::cout << "endPressPoint: " << Input()->getMousePosition().x << " " << Input()->getMousePosition().y << std::endl;
        // std::cout << "setVelocity: " << velocity.x << " " << velocity.y << std::endl;
    }
}

float Ball::getDistance(Vector2D startPoint, Vector2D endPoint)
{
    return SDL_sqrt(SDL_pow(endPoint.x - startPoint.x, 2) + SDL_pow(endPoint.y - startPoint.y, 2));
}

float Ball::getLaunchStrength(Vector2D startPoint, Vector2D endPoint)
{
    float distance = getDistance(startPoint, endPoint) * sensibilidad;
    distance = distance > maxLaunchForce ? maxLaunchForce : distance;

    return distance;
}

void Ball::setVelocity(Vector2D startPoint, Vector2D endPoint)
{
    float force = getLaunchStrength(startPoint, endPoint);
    Vector2D dir = (startPoint - endPoint).normalized();
    dir *= force;
    velocity = dir;
}

void Ball::setVelocity(Vector2D vel)
{
    velocity = vel;
}

void Ball::receiveNetworkMessage(NetworkMessage *msg)
{
    if (msg->type == BALL_POS && !mainBall)
    {
        BallPosMessage *hitMsg = static_cast<BallPosMessage *>(msg);
        transform->getPosition() = Vector2D(hitMsg->xForce, hitMsg->yForce);
        state = BallState::MOVING;
    }
    else if (msg->type == TURN_END && mainBall) // Esto significa que el otro jugador ha acabado su turno
        playerTurn = true;
    else if (msg->type == BALL_HIT)
        this->playSound("collision");
}

float Ball::getCurrentLaunchForce() const
{
    return currentLaunchForce;
}

Vector2D Ball::getCurrentLaunchDirection() const
{
    return currentLaunchDirection.normalized();
}

float Ball::getMaxLaunchForce() const
{
    return maxLaunchForce;
}

float Ball::getMininumThreshold() const
{
    return mininumThreshold;
}

void Ball::sideCollision()
{
    velocity.x = -velocity.x;
}

void Ball::topDownCollision()
{
    velocity.y = -velocity.y;
}

bool Ball::isMainBall() const
{
    return mainBall;
}

Vector2D Ball::getVelocity() const
{
    return velocity;
}