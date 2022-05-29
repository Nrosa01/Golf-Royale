#include <iostream>
#include <SDL2/SDL.h>
#include "Texture.h"
#include "SDLApp.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

int main()
{
    SDLApp *app = new SDLApp(SCREEN_WIDTH, SCREEN_HEIGHT, "Golf Royale");
    Texture *texture = new Texture(app->getRenderer(), "assets/img/GolfRoyaleBg.png");

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

        // Clear screen
        SDL_SetRenderDrawColor(app->getRenderer(), 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(app->getRenderer());

        // Render entities
        SDL_Rect rect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

        texture->render(rect);

        // Update screen
        SDL_RenderPresent(app->getRenderer());
    }

    delete app;
    return 0;
}