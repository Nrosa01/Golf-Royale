#pragma once
#include "../EC/Entity.h"
#include "../EC/EventHandler.h"
#include <list>

class SDLApp;

class GameState
{
protected:
	list<Entity*> gameObjects;
	list<EventHandler*> eventHandlers;
	SDLApp* game;

	GameState(SDLApp* g) { game = g; };
public:
	virtual void update(float deltaTime) {
		for (Entity* o : gameObjects) o->update(deltaTime);
	}
	virtual void render() { for (Entity* o : gameObjects) o->render(); }
	virtual void handleEvent(SDL_Event& e) { for (EventHandler* h : eventHandlers) if (h->handleEvent(e)) return; }

	virtual ~GameState()
	{
		for (Entity* o : gameObjects) delete o;
	}
};