// Copyright © 2022 Rioni

// Permission is hereby granted, free of charge, to any person obtaining a copy of this
// software and associated documentation files (the “Software”), to deal in the Software without
// restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute,
// sublicense, and/or sell copies of the Software, and to permit persons to whom the Software
// is furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall
// be included in all copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
// THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
// WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR
// IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#include <iostream>
#include <SDL.h>
#include "SDLUtils/Texture.h"
#include "SDLUtils/SDLApp.h"
#include "SDLUtils/TimeManager.h"
#include "EC/Entity.h"
#include "EC/Components/Renderer.h"
#include "GameState/MainMenuState.h"
#include "ParseTools/ParseTools.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define TARGET_FRAME_RATE 60
constexpr uint32_t FRAME_TIME_MS = 1000 / TARGET_FRAME_RATE;

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        std::cerr << "Usage: " << argv[0] << " <address> <port>\n";
        return 1;
    }

    // Check address format
    if (!ParseTool::is_address(argv[1]))
    {
        std::cerr << "Invalid address format.\n";
        return 1;
    }

    // Check port format
    uint32_t port = ParseTool::is_number(argv[2]) ? std::stoi(argv[2]) : -1;

    if (port < 0 || port > 65535)
    {
        std::cerr << "Invalid port number.\n";
        return 1;
    }

    SDLApp app(SCREEN_WIDTH, SCREEN_HEIGHT, "Golf Royale");
    app.initNetClient(argv[1], argv[2]);
    app.loadTextures("assets/images/");
    app.loadFonts("assets/fonts/");
    app.loadAudio("assets/sounds/");

    if(app.isExitRequested())
        return 1;

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
        Input()->updateState();

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
                Input()->onKeyDown(key);
                break;
            case SDL_KEYUP:
                Input()->onKeyUp(key);
                break;
            case SDL_MOUSEBUTTONDOWN:
                Input()->onMouseButtonDown(e.button);
                break;
            case SDL_MOUSEBUTTONUP:
                Input()->onMouseButtonUp(e.button);
                break;
            case SDL_MOUSEMOTION:
                // This is usually implemented as a callback but for now it will be this way, just for testing...
                Input()->setMouseMotion(Vector2D(e.motion.xrel, e.motion.yrel));
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

        time.updateTimeRegistry(SDL_GetTicks());
    }

    return 0;
}