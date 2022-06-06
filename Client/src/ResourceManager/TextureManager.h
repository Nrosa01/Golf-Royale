#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include "ResourceManager.h"
#include <SDL2/SDL.h>
#include "../SDLUtils/Texture.h"

class TextureManager : public ResourceManager<Texture>
{
    public:
    TextureManager(SDL_Renderer* renderer) : ResourceManager("texture", {"png", "jpg"}, [renderer](std::string filePath)
    {
         // As this is simple project, there are no animations so all textures are 1*1, they are not spritesheets
         // If I had more time, I would load these settings from a json
        Texture *texture = new Texture(renderer);
        texture->load(filePath.c_str(), 1, 1);
        return texture;
    }) {}
};

#endif