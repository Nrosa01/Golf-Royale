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
        if (checkSideCollision(renderer, obstacle, deltaTime))
            ball->sideCollision();

        if (checkTopDownCollision(renderer, obstacle, deltaTime))
            ball->topDownCollision();
    }
}

bool BallCollisionManager::checkIntersection(Renderer *ball, Renderer *obstacle, float deltaTime)
{
    SDL_Rect ballRect = ball->getDestRectAt(this->ball->getNextPosition(deltaTime));
    SDL_Rect obstacleRect = obstacle->getDestRect();

    return SDL_HasIntersection(&ballRect, &obstacleRect);
}

bool BallCollisionManager::checkSideCollision(Renderer *ball, Renderer *obstacle, float deltaTime)
{
    SDL_Rect ballRect = ball->getDestRectAt(this->ball->getNextPosition(deltaTime));
    SDL_Rect obstacleRect = obstacle->getDestRect();

    if (checkIntersection(ball, obstacle, deltaTime))
    {
        if (ballRect.x + ballRect.w >= obstacleRect.x && ballRect.x <= obstacleRect.x + obstacleRect.w)
            return true;
    }

    return false;
}

bool BallCollisionManager::checkTopDownCollision(Renderer *ball, Renderer *obstacle, float deltaTime)
{
    SDL_Rect ballRect = ball->getDestRectAt(this->ball->getNextPosition(deltaTime));
    SDL_Rect obstacleRect = obstacle->getDestRect();

    if (checkIntersection(ball, obstacle, deltaTime))
    {
        if (ballRect.y + ballRect.h >= obstacleRect.y && ballRect.y <= obstacleRect.y + obstacleRect.h)
            return true;
    }

    return false;
}