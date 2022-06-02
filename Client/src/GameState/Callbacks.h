#ifndef BUTTONCALLBACKS_H
#define BUTTONCALLBACKS_H

#include <functional>
class GameState;

using GameStateCallback = std::function<void(GameState*, void*)>;

extern void popState(GameState* state, void* args = nullptr);
extern void changeState(GameState *state, void *args);
extern void pushState(GameState* state, void* args);
extern void exitGame(GameState* state, void* args);

#endif