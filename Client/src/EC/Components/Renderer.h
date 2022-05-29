#ifndef RENDERER_H
#define RENDERER_H

#include "../Component.h"
#include "Transform.h"
#include "../../SDLUtils/Texture.h"
#include <SDL2/SDL.h>

class Renderer : public Component
{
public:
    Renderer(Transform* transform, Texture* texture) : Component("Renderer"), transform(transform), texture(texture) {};
    virtual ~Renderer() {};
    virtual void update(float deltaTime) {};
    virtual void render() 
    {
        SDL_Rect destRect;
        destRect.x = transform->GetPosition().getX();
        destRect.y = transform->GetPosition().getY();
        destRect.w = transform->GetScale() * texture->getW();
        destRect.h = transform->GetScale() * texture->getH();

        texture->render(destRect);
    };
private:
Transform* transform;
Texture* texture;
};

#endif