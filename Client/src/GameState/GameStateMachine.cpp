#include "GameStateMachine.h"

GameStateMachine::GameStateMachine(GameState *state)
{
    pushState(state);
}

GameStateMachine::GameStateMachine() {}

GameStateMachine::~GameStateMachine()
{
    while (!states.empty())
        popState();
}

GameState *GameStateMachine::currentState()
{
    return states.top();
}

void GameStateMachine::update(float deltaTime)
{
    states.top()->update(deltaTime);
}

void GameStateMachine::render()
{
    states.top()->render();
}

void GameStateMachine::pushState(GameState *stateToPush)
{
    if (!states.empty())
        states.top()->onStateExit();

    states.push(stateToPush);
    stateToPush->onStateEnter();
}

void GameStateMachine::changeState(GameState *stateToPush)
{
    if (!states.empty())
    {
        states.top()->onStateExit();
        delete states.top();
        states.pop();
    }

    states.push(stateToPush);
    stateToPush->onStateEnter();
}

void GameStateMachine::popState()
{
    if (states.empty())
        return;

    states.top()->onStateExit();
    delete states.top();
    states.pop();

    if (!states.empty())
        states.top()->onStateEnter();
}