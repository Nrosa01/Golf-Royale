#ifndef TEXTRENDERER_H
#define TEXTRENDERER_H

#include "../Component.h"
#include "../../MathUtils/Vector2D.h"
#include <SDL2/SDL.h>

class Texture;

class TextRenderer : public Component
{
public:
    TextRenderer(std::string text, std::string font, int fontSize, SDL_Color textColor = {255, 255, 255, 255}, Vector2D offset = Vector2D(0, 0));
    virtual ~TextRenderer();
    virtual void init();
    virtual void render();
    void setText(const char *text);
    void setText(std::string text);

private:
    std::string text;
    std::string font;
    int fontSize;
    SDL_Color textColor;
    Vector2D offset;

    Vector2D initialScale;
};

#endif