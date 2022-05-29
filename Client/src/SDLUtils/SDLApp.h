#ifndef SDLAppH
#define SDLAppH

#include <SDL2/SDL.h>
#include <unordered_map>
#include <vector>

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

    SDL_Renderer* getRenderer() const { return renderer; };
private:
    SDL_Window* window;
    SDL_Renderer* renderer;

    std::unordered_map<std::string, Texture*> textures;
};

#endif