#include "SDLApp.h"
#include "SDLEntity.h"
#include <SDL2/SDL.h>
#include <iostream>

SDLApp::SDLApp(int width, int height, const char* title)
{
    //Init sdl and create window
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return;
    }
    else
    {
        std::cout << "SDL initialized!" << std::endl;
    }

    //Create window
    window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    if(window == NULL)
    {
        std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return;
    }
    else
    {
        std::cout << "Window created!" << std::endl;
    }

    //Create renderer for window
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(renderer == NULL)
    {
        std::cout << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return;
    }
    else
    {
        std::cout << "Renderer created!" << std::endl;
    }
}

SDLApp::~SDLApp()
{
    //Free resources and close SDL
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void SDLApp::update(float deltaTime)
{
    // Update entities
    for(SDLEntity* entity : entities)
        entity->update(deltaTime);
}

void SDLApp::render()
{
    // Clear screen
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);

    // Render entities
    for(SDLEntity* entity : entities)
        entity->render();

    // Update screen
    SDL_RenderPresent(renderer);
}