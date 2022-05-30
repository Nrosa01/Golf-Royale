#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include <SDL2/SDL.h>

class EventHandler
{
public:
    virtual bool handleEvent(SDL_Event &e) = 0;
};

#endif