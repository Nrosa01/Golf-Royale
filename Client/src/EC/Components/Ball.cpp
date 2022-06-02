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
    transform = this->ent->GetTransform();
    renderer = this->ent->GetComponent<Renderer>();
    sensibilidad = 10.0f;
}

void Ball::update(float deltaTime)
{
    handleMain();

    if (state != BallState::MOVING)
        return;

    if (isOutOfBoundsX(deltaTime))
    {
        velocity.x = -velocity.x;
        this->playSound("collision");
    }
    if (isOutOfBoundsY(deltaTime))
    {
        velocity.y = -velocity.y;
        this->playSound("collision");
    }

    if (state != BallState::MOVING)
        return;

    // Update position
    transform->GetPosition().x += velocity.x * deltaTime;
    transform->GetPosition().y += velocity.y * deltaTime;

    // Simulate friction
    if (velocity.Magnitude() > mininumThreshold)
    {
        float vel = velocity.Magnitude() - (friction * deltaTime);
        vel = vel < mininumThreshold ? 0 : vel;
        velocity = velocity.Normalized() * vel;
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
    // if (!this->mainBall || !playerTurn)
    //     return;

    Vector2D mousePos = Input()->GetMousePosition();

    if (Input()->IsMouseButtonDown(0) && state == BallState::IDLE)
    {
        state = BallState::PRESSED;
        startPressPoint = mousePos;
        // std::cout << "startPressPoint: " << startPressPoint.x << " " << startPressPoint.y << std::endl;
    }

    if (state == BallState::PRESSED)
    {
        currentLaunchForce = getLaunchStrength(startPressPoint, mousePos);
        currentLaunchDirection = (startPressPoint - mousePos).Normalized();
    }

    if (!Input()->IsMouseButtonDown(0) && state == BallState::PRESSED)
    {
        state = BallState::MOVING;
        setVelocity(startPressPoint, mousePos);
        currentLaunchForce = 0;

        if (velocity.Magnitude() > mininumThreshold)
        {
            this->playSound("swing");
            BallHitMessage hitMsg(velocity.x, velocity.y);
            sendNetworkMessage(hitMsg);
        }
        // std::cout << "endPressPoint: " << Input()->GetMousePosition().x << " " << Input()->GetMousePosition().y << std::endl;
        // std::cout << "setVelocity: " << velocity.x << " " << velocity.y << std::endl;
    }
}

bool Ball::isOutOfBoundsX(float deltaTime)
{
    int screenWidth = this->ent->GetGame()->getWidth();
    int posToCheck = transform->GetPosition().x + velocity.x * deltaTime;
    int posToCheckRight = posToCheck + renderer->getWidth() / 2 * transform->GetScale().x;
    int posToCheckLeft = posToCheck - renderer->getWidth() / 2 * transform->GetScale().x;

    int postToCheckOtherRight = posToCheck - renderer->getWidth() / 2 * transform->GetScale().x;
    int postToCheckOtherLeft = posToCheck + renderer->getWidth() / 2 * transform->GetScale().x;

    // If we are mainBall, we are retriscted to the left half of the screen
    if (mainBall)
        return posToCheckRight > screenWidth / 2 || posToCheckLeft < 0;
    else
        return postToCheckOtherRight < screenWidth / 2 || postToCheckOtherLeft > screenWidth;
}

bool Ball::isOutOfBoundsY(float deltaTime)
{
    int screenHeight = this->ent->GetGame()->getHeight();
    int posToCheck = transform->GetPosition().y + velocity.y * deltaTime;
    int posToCheckUP = posToCheck - transform->GetScale().y * renderer->getHeight() / 2;
    int posToCheckDOWN = posToCheck + transform->GetScale().y * renderer->getHeight() / 2;

    return posToCheckDOWN > screenHeight || posToCheckUP < 0;
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
    Vector2D dir = (startPoint - endPoint).Normalized();
    dir *= force;
    velocity = dir;
}

void Ball::receiveNetworkMessage(NetworkMessage &msg)
{
    if (msg.type == BALL_HIT && !mainBall)
    {
        BallHitMessage *hitMsg = &static_cast<BallHitMessage &>(msg);
        velocity.x = hitMsg->xForce;
        velocity.y = hitMsg->yForce;
        state = BallState::MOVING;
    }
    else if (msg.type == TURN_END) // Esto significa que el otro jugador ha acabado su turno
        playerTurn = true;
}

float Ball::getCurrentLaunchForce() const
{
    return currentLaunchForce;
}

Vector2D Ball::getCurrentLaunchDirection() const
{
    return currentLaunchDirection.Normalized();
}

float Ball::getMaxLaunchForce() const
{
    return maxLaunchForce;
}

float Ball::getMininumThreshold() const
{
    return mininumThreshold;
}