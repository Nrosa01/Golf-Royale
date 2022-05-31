#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <SDL2/SDL.h>
#include <vector>
using namespace std;

class SDLApp;
class Entity;

#define TRANSITION_TIME 0.15f

class GameState
{
protected:
	vector<Entity*> entities;
	SDLApp* app;

	GameState(SDLApp* g);
public:
	virtual void update(float deltaTime);
	virtual void render();
	virtual ~GameState();
};

#endif