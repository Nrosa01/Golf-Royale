#ifndef SDLAppH
#define SDLAppH

#include <SDL2/SDL.h>
#include <unordered_map>
#include <vector>
#include "../GameState/GameStateMachine.h"
#include "InputSytem.h"

class Texture;

class SDLApp
{
public:
    SDLApp(int width, int height, const char* title);
    ~SDLApp();

    void loadTextures(const char* pathName);
    Texture* getTexture(std::string name) const;
    void update(float deltaTime);
    void render();
    void handleEvent(SDL_Event& e);
    void pushState(GameState* stateToPush);
    int getWidth() const;
    int getHeight() const;

    SDL_Renderer* getRenderer() const { return renderer; };
private:
    SDL_DisplayMode getDisplayMOde() const;

    SDL_Window* window;
    SDL_Renderer* renderer;
    GameStateMachine* gameStateMachine;
    std::unordered_map<std::string, Texture*> textures;
    int width;
    int height;
    InputSystem* input;
};

#endif