#ifndef GAMESTATEMACHINE_H
#define GAMESTATEMACHINE_H

#include <stack>
#include "GameState.h"

using namespace std;

class GameStateMachine
{
private:
	stack<GameState*> states;
public:
	GameStateMachine(GameState* state);
    GameStateMachine();
	~GameStateMachine();
	GameState* currentState();
    void update(float deltaTime);
    void render();
	void receiveNetworkMessage(NetworkMessage* msg);
	void pushState(GameState* stateToPush);
	void changeState(GameState* stateToPush);
	void popState();
	uint getStateCount();
};

#endif