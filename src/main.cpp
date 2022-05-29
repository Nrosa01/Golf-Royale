#include <iostream>
#include <SDL2/SDL.h>
#include "Texture.h"
#include "SDLApp.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

int main()
{
    SDLApp *app = new SDLApp(SCREEN_WIDTH, SCREEN_HEIGHT, "Golf Royale");
    app->loadTextures("assets/images/");

    // Main loop flag
    bool quit = false;

    // Event handler
    SDL_Event e;

    // While application is running
    while (!quit)
    {
        // Handle events on queue
        while (SDL_PollEvent(&e) != 0)
        {
            // User requests quit
            if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE))
            {
                quit = true;
            }
        }
    }

    delete app;
    return 0;
}