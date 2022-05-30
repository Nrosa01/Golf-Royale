#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <SDL2/SDL.h>
#include <list>
using namespace std;

class SDLApp;
class Entity;
class EventHandler;

class GameState
{
protected:
	list<Entity*> entities;
	list<EventHandler*> eventHandlers;
	SDLApp* game;

	GameState(SDLApp* g);
public:
	virtual void update(float deltaTime);
	virtual void render();
	virtual void handleEvent(SDL_Event& e);
	virtual ~GameState();
};

#endif