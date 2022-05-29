#include <iostream>
#include <SDL2/SDL.h>
#include "SDLUtils/Texture.h"
#include "SDLUtils/SDLApp.h"
#include "EC/Entity.h"
#include "EC/Components/Renderer.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

int main()
{
    SDLApp app(SCREEN_WIDTH, SCREEN_HEIGHT, "Golf Royale");
    app.loadTextures("assets/images/");

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

            //clear renderer
            SDL_SetRenderDrawColor(app.getRenderer(), 0xFF, 0xFF, 0xFF, 0xFF);
            SDL_RenderClear(app.getRenderer());

    
            //Update screen
            SDL_RenderPresent(app.getRenderer());
        }
    }

    return 0;
}