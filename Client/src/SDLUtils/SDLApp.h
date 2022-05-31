#ifndef SDLAppH
#define SDLAppH

#include <SDL2/SDL.h>
#include <unordered_map>
#include <vector>
#include "../GameState/GameStateMachine.h"
#include "InputSytem.h"
#include <SDL2/SDL_ttf.h>

class Texture;

class SDLApp
{
public:
    SDLApp(int width, int height, const char *title);
    ~SDLApp();

    void loadTextures(const char *pathName);
    Texture *getTexture(std::string name) const;
    void loadFonts(const char *pathName);
    TTF_Font *getFont(std::string name) const;
    void update(float deltaTime);
    void render();
    void renderText(float p_x, float p_y, const char *p_text, TTF_Font *font, SDL_Color textColor);
    void renderText(float p_x, float p_y, const char *p_text, std::string fontName, SDL_Color textColor);
    void renderTextCenter(float p_x, float p_y, const char *p_text, std::string fontName, SDL_Color textColor);
    void renderTextCenter(float p_x, float p_y, const char *p_text, TTF_Font *font, SDL_Color textColor);
    void pushState(GameState *stateToPush);
    int getWidth() const;
    int getHeight() const;

    SDL_Renderer *getRenderer() const { return renderer; };

private:
    SDL_DisplayMode getDisplayMOde() const;

    SDL_Window *window;
    SDL_Renderer *renderer;
    GameStateMachine *gameStateMachine;
    std::unordered_map<std::string, Texture *> textures;
    std::unordered_map<std::string, TTF_Font *> fonts;
    int width;
    int height;
    InputSystem *input;
};

#endif