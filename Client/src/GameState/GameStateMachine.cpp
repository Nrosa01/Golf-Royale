#include "GameStateMachine.h"

GameStateMachine::GameStateMachine(GameState *state)
{
    states.push(state);
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
    states.push(stateToPush);
}

void GameStateMachine::changeState(GameState *stateToPush)
{
    popState();
    states.push(stateToPush);
}

void GameStateMachine::popState()
{
    if (states.empty())
        return;

    delete states.top();
    states.pop();
}