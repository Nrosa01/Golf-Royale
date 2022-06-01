#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <SDL2/SDL.h>
#include <vector>
#include <string>
#include "../MathUtils/Vector2D.h"
#include "Callbacks.h"
#include "../Network/NetworkMessage.h"

using namespace std;

class SDLApp;
class Entity;

#define TRANSITION_TIME 0.15f
class Transitioner;

class GameState
{
protected:
	vector<Entity *> entities;
	SDLApp *app;

	GameState(SDLApp *g);

public:
	virtual void update(float deltaTime);
	virtual void render();
	virtual void onStateEnter(); // Called when state is pushed or when reached after popped other
	virtual void onStateExit(); // Called when state is popped from stack
	virtual void receiveNetworkMessage(NetworkMessage& msg);
    void sendNetworkMessage(NetworkMessage &msg);
    void sendNetworkMessage(NetworkMessage &&msg);
	virtual ~GameState();
	void startExitTransitionTimer(GameStateCallback callback = nullptr, void* args = nullptr);
	void addTransitioner(Entity* e);
	Entity* createEntity(Vector2D pos, Vector2D scale = Vector2D(1,1), string textureName = "");
	SDLApp* getApp();
private:
	vector<Transitioner *> transitioners;
	GameStateCallback endExitTransitionFinishCallback;
	bool startTransition;
	float timer;
	void* args;
};

#endif