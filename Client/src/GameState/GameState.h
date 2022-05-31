#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <SDL2/SDL.h>
#include <list>
using namespace std;

class SDLApp;
class Entity;

class GameState
{
protected:
	list<Entity*> entities;
	SDLApp* game;

	GameState(SDLApp* g);
public:
	virtual void update(float deltaTime);
	virtual void render();
	virtual ~GameState();
};

#endif