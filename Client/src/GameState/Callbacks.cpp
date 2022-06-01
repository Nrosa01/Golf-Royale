#include "Callbacks.h"
#include "GameState.h"
#include "../SDLUtils/SDLApp.h"
#include <iostream>

void popState(GameState *state, void *args)
{
    state->getApp()->popState();
}

void pushState(GameState *state, void *args)
{
    GameState *newState = reinterpret_cast<GameState *>(args);
    state->getApp()->pushState(newState);
}

void exitGame(GameState *state, void *args)
{
    state->getApp()->quit();
}
