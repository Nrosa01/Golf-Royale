#ifndef ENT_RENDERER_H
#define ENT_RENDERER_H

#include "../Component.h"
#include <SDL2/SDL.h>

class Texture;
class Transform;

class Renderer : public Component
{
public:
    Renderer(Texture* texture);
    virtual ~Renderer();
    virtual void init();
    virtual void render();
    int getWidth();
    int getHeight();
    SDL_Rect getDestRectCentered();
    SDL_Rect getDestRect();
    SDL_Rect getDestRectAt(Vector2D position);
private:
Transform* transform;
Texture* texture;
};

#endif