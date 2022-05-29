#ifndef SDLAppH
#define SDLAppH

#include <SDL2/SDL.h>
#include <vector>

class SDLEntity;

class SDLApp
{
public:
    SDLApp(int width, int height, const char* title);
    ~SDLApp();

    void update(float deltaTime);
    void render();

private:
    SDL_Window* window;
    SDL_Renderer* renderer;

    std::vector<SDLEntity*> entities;
};

#endif