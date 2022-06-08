#ifndef SOUNDS_MANAGER_H
#define SOUNDS_MANAGER_H

#include "ResourceManager.h"
#include <SDL2/SDL_mixer.h>

class SoundsManager : public ResourceManager<Mix_Chunk>
{
public:
    SoundsManager() : ResourceManager("sound", {"wav", "mp3"}, [](std::string filePath)
                                      { return Mix_LoadWAV(filePath.c_str()); }) {}

    ~SoundsManager() { clear(); }

    virtual void freeResource(Mix_Chunk *sound)
    {
        Mix_FreeChunk(sound);
    }

    void play(std::string name)
    {
        auto sound = get(name);
        if (sound != nullptr)
            Mix_PlayChannel(-1, sound, 0);
    }
};

#endif