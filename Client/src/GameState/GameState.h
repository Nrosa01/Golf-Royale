#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <SDL2/SDL.h>
#include <vector>
#include <string>
#include "../MathUtils/Vector2D.h"
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
	virtual void onStateEnter();
	virtual void onStateExit();
	virtual ~GameState();
	void startExitTransitionTimer();
	void addTransitioner(Entity* e);
	Entity* createEntity(Vector2D pos, Vector2D scale = Vector2D(1,1), string textureName = "");

private:
	vector<Transitioner *> transitioners;
	bool startTransition;
	float timer;
};

#endif