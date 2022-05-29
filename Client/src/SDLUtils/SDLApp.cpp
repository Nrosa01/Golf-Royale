#include "SDLApp.h"
#include "SDLEntity.h"
#include <SDL2/SDL.h>
#include <iostream>
#include <dirent.h>
#include "Texture.h"

SDLApp::SDLApp(int width, int height, const char *title)
{
    // Init sdl and create window
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return;
    }
    else
        std::cout << "SDL initialized!" << std::endl;

    // Create window
    window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return;
    }
    else
        std::cout << "Window created!" << std::endl;

    // Create renderer for window
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL)
    {
        std::cout << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return;
    }
    else
        std::cout << "Renderer created!" << std::endl;
}

SDLApp::~SDLApp()
{
    // Free resources and close SDL
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void SDLApp::update(float deltaTime)
{
    // Update entities
    for (SDLEntity *entity : entities)
        entity->update(deltaTime);
}

void SDLApp::render()
{
    // Clear screen
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);

    // Render entities
    for (SDLEntity *entity : entities)
        entity->render();

    // Update screen
    SDL_RenderPresent(renderer);
}

void SDLApp::loadTextures(const char *pathName)
{
    // Load textures
    std::cout << "Loading textures from " << pathName << "..." << std::endl;

    // Using dirent, check if pathName is a directory
    DIR *dir = opendir(pathName);

    // If it is a directory, load all files in it with extension .png or .jpg
    if (dir != nullptr)
    {
        // Get all files in directory
        struct dirent *ent;
        while ((ent = readdir(dir)) != nullptr)
        {
            // Get file extension
            std::string fileName = ent->d_name;
            std::string ext = fileName.substr(fileName.find_last_of(".") + 1);
            std::string fileNameWithoutExt = fileName.substr(0, fileName.find_last_of("."));

            // If file extension is .png or .jpg, load texture
            if (ext == "png" || ext == "jpg")
            {
                std::string filePath = pathName;
                filePath.append("/");
                filePath.append(fileName);

                // Load texture
                Texture *texture = new Texture(renderer);
                // As this is simple project, there are no animations so all textures are 1*1, they are not spritesheets
                // If I had more time, I would load these settings from a json
                texture->load(filePath.c_str(), 1, 1); 
                std::cout << "Loaded texture " << fileNameWithoutExt << std::endl;
                textures.insert(std::pair<std::string, Texture *>(fileNameWithoutExt, texture));
            }
        }

        std::cout << "Textures loaded!" << std::endl;
    }
    else // If pathName is not a directory, we throw an error message
        std::cout << "Path " << pathName << " is not a directory!" << std::endl;
}

Texture* SDLApp::getTexture(std::string name) const
{
    // Get texture from map
    std::unordered_map<std::string, Texture *>::const_iterator it = textures.find(name);
    if (it != textures.end())
        return it->second;
    else
        return nullptr;
}