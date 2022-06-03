#include "BallCollisionManager.h"
#include "Renderer.h"
#include "Transform.h"
#include "Ball.h"
#include "../Entity.h"

BallCollisionManager::BallCollisionManager(std::vector<Renderer *> *obstacles) : Component(typeid(BallCollisionManager).name()), obstacles(obstacles){};

BallCollisionManager::~BallCollisionManager(){};

void BallCollisionManager::init()
{
    transform = this->ent->GetComponent<Transform>();
    renderer = this->ent->GetComponent<Renderer>();
    ball = this->ent->GetComponent<Ball>();
    main = ball->isMainBall();

    if (transform == nullptr)
    {
        std::cout << "BallCollisionManager::init() - ERROR: Entity does not have a Transform component!" << std::endl;
        return;
    }

    if (renderer == nullptr)
    {
        std::cout << "BallCollisionManager::init() - ERROR: Entity does not have a Renderer component!" << std::endl;
        return;
    }
}

void BallCollisionManager::update(float deltaTime)
{
    if (obstacles->empty())
        return;

    for (auto obstacle : *obstacles)
    {
        if (checkIntersection(renderer, obstacle))
        {
            Vector2D normal =  getCollisionNormal(renderer, obstacle, ball->getVelocity());
            takeBodyOutOfCollision(renderer, obstacle, normal);
            notifyCollision(normal);
            //this->ball->setVelocity(Vector2D());
        }
    }
}

bool BallCollisionManager::checkIntersection(Renderer *ball, Renderer *obstacle)
{
    SDL_Rect ballRect = ball->getDestRectCentered();
    SDL_Rect obstacleRect = obstacle->getDestRectCentered();

    return SDL_HasIntersection(&ballRect, &obstacleRect);
}

bool BallCollisionManager::checkIntersection(Entity *obstacle)
{
    Renderer *obstacleRenderer = obstacle->GetComponent<Renderer>();

    return checkIntersection(renderer, obstacleRenderer);
}

Vector2D BallCollisionManager::getCollisionNormal(Renderer *ball, Renderer *obstacle, Vector2D ballVelocity)
{
    SDL_Rect ballRect = ball->getDestRect();
    SDL_Rect obstacleRect = obstacle->getDestRect();

    Vector2D ballCenter = Vector2D(ballRect.x, ballRect.y);
    Vector2D obstacleCenter = Vector2D(obstacleRect.x, obstacleRect.y);

    // Normal can be c1,0 -1,0 or 0,1 or 0,-1
    Vector2D collisionDir = obstacleCenter - ballCenter;

    return makeUnitary(collisionDir);
}

Vector2D BallCollisionManager::makeUnitary(Vector2D vector)
{
    Vector2D unitary;

    // We take the biggest value of the vector in absolute value and make it 1 in that direction
    // The other value will be 0.

    if (abs(vector.x) > abs(vector.y))
        unitary.x = vector.x > 0 ? 1 : -1;
    else
        unitary.y = vector.y > 0 ? 1 : -1;

    return unitary;
}

void BallCollisionManager::takeBodyOutOfCollision(Renderer *ball, Renderer *obstacle, Vector2D collisionNormal)
{
    SDL_Rect ballRect = ball->getDestRectCentered();
    SDL_Rect obstacleRect = obstacle->getDestRectCentered();
    Vector2D &ballPos = transform->GetPosition();

    // We need to move the ball to the side of the obstacle.
    if (abs(collisionNormal.x) > 0.1)
    {
       if(collisionNormal.x > 0)
            ballPos.x = obstacleRect.x - ballRect.w / 2 - 1;
        else
            ballPos.x = obstacleRect.x + obstacleRect.w + ballRect.w / 2 + 1;
    }
    else if (abs(collisionNormal.y) > 0.1)
    {
        if(collisionNormal.y > 0)
            ballPos.y = obstacleRect.y - ballRect.h / 2 - 1;
        else
            ballPos.y = obstacleRect.y + obstacleRect.h + ballRect.h / 2 + 1;
    }
}

void BallCollisionManager::notifyCollision(Vector2D collisionNormal)
{
    if (abs(collisionNormal.x) > 0.1)
        this->ball->sideCollision();
    else if (abs(collisionNormal.y) > 0.1)
        this->ball->topDownCollision();
}