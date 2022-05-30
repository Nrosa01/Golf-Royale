#include <iostream>
#include <SDL2/SDL.h>
#include "SDLUtils/Texture.h"
#include "SDLUtils/SDLApp.h"
#include "SDLUtils/TimeManager.h"
#include "EC/Entity.h"
#include "EC/Components/Renderer.h"
#include "GameState/MainMenuState.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define TARGET_FRAME_RATE 60
const uint32_t FRAME_TIME_MS = (uint32_t)floor((1 / TARGET_FRAME_RATE) * 1000);

int main()
{
    SDLApp app(SCREEN_WIDTH, SCREEN_HEIGHT, "Golf Royale");
    app.loadTextures("assets/images/");
    app.pushState(new MainMenuState(&app));

    // Main loop flag
    bool quit = false;

    // Event handler
    SDL_Event e;
    TimeManager time;

    // While application is running
    while (!quit)
    {
        time.frameStartTime = SDL_GetTicks();

        // Handle events on queue
        while (SDL_PollEvent(&e) != 0)
        {
            // User requests quit
            if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE))
                quit = true;
            else
                app.handleEvent(e);
        }

        app.update(time.deltaTime);
        app.render();

        // Calculate frame time
        Uint32 frameTime = SDL_GetTicks() - time.frameStartTime;

        if (frameTime < FRAME_TIME_MS)
        {
            // Sleep the remaining frame time
            SDL_Delay(FRAME_TIME_MS - frameTime);
        }

        time.UpdateTimeRegistry(SDL_GetTicks());
    }

    return 0;
}