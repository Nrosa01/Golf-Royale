#ifndef SDL_TEXT_RENDERER_H
#define SDL_TEXT_RENDERER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <unordered_map>

class Texture;

class SDLTextRenderer
{
public:
    SDLTextRenderer(SDL_Renderer *renderer, uint32_t maxFontSize);
    ~SDLTextRenderer();

    void renderText(float p_x, float p_y, const char *p_text, TTF_Font *font, int size, SDL_Color textColor);
    void clear();
    int getNumOfLoadedTextures() const;
private:
    Texture* createTextTexture(const char *p_text, TTF_Font *font);
    Texture* getTexture(const char *p_text, TTF_Font *font);

private:
    SDL_Renderer *renderer;
    uint32_t maxFontSize;
    std::unordered_map<TTF_Font*, std::unordered_map<std::string, Texture*>> fontCache;
};

#endif