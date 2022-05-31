#include <iostream>
#include <SDL2/SDL.h>
#include "SDLUtils/Texture.h"
#include "SDLUtils/SDLApp.h"
#include "SDLUtils/TimeManager.h"
#include "EC/Entity.h"
#include "EC/Components/Renderer.h"
#include "GameState/MainMenuState.h"
#include "GameState/PlayState.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define TARGET_FRAME_RATE 60
const uint32_t FRAME_TIME_MS = (uint32_t)floor((1 / TARGET_FRAME_RATE) * 1000);

int main()
{
    SDLApp app(SCREEN_WIDTH, SCREEN_HEIGHT, "Golf Royale");
    app.loadTextures("assets/images/");
    app.loadFonts("assets/fonts/");
    app.loadAudio("assets/sounds/");
    app.pushState(new MainMenuState(&app));

    // Main loop flag
    bool quit = false;

    // Event handler
    SDL_Event e;
    TimeManager time;

    // While application is running
    while (!quit && !app.isExitRequested())
    {
        time.frameStartTime = SDL_GetTicks();
        Input()->UpdateState();

        // Handle events on queue
        while (SDL_PollEvent(&e) != 0)
        {
            auto key = e.key.keysym.sym;
            switch (e.type)
            {
            case SDL_QUIT:
                quit = true;
            case SDL_KEYDOWN:
                if (key == SDLK_ESCAPE)
                    quit = true;
                Input()->OnKeyDown(key);
                break;
            case SDL_KEYUP:
                Input()->OnKeyUp(key);
                break;
            case SDL_MOUSEBUTTONDOWN:
                Input()->OnMouseButtonDown(e.button);
                break;
            case SDL_MOUSEBUTTONUP:
                Input()->OnMouseButtonUp(e.button);
                break;
            case SDL_MOUSEMOTION:
                // This is usually implemented as a callback but for now it will be this way, just for testing...
                Input()->SetMouseMotion(Vector2D(e.motion.xrel, e.motion.yrel));
                break;
            default:
                // std::cout << "Default (" << eventHandler.type << ")\n";
                break;
            }
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