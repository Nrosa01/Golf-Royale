#ifndef TIME_MANAGER_H
#define TIME_MANAGER_H

#include <SDL2/SDL_stdinc.h>

struct TimeManager
{
public:
	float deltaTime = 0;

	Uint32 frameStartTime = 0;
	Uint32 timeSinceAppStartMS = 0;

	Uint32 updateTimeRegistry(Uint32 currentTime) {
		deltaTime = (currentTime - frameStartTime) / 1000.0f;
		timeSinceAppStartMS += (currentTime - frameStartTime);
		return deltaTime;
	}
};

#endif