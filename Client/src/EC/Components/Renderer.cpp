#include "Renderer.h"
#include "../Entity.h"
#include "Transform.h"
#include "../../SDLUtils/Texture.h"
#include <SDL2/SDL.h>

Renderer::Renderer(Texture *texture) : Component("Renderer"), transform(nullptr), texture(texture){};

Renderer::~Renderer(){};

void Renderer::init()
{
    transform = this->ent->GetTransform();
}

void Renderer::render()
{
    SDL_Rect destRect;
    int textW = texture->getW();
    int textH = texture->getH();
    destRect.x = transform->GetPosition().getX() - textW / 2;
    destRect.y = transform->GetPosition().getY() - textH / 2;
    destRect.w = transform->GetScale().x * textW;
    destRect.h = transform->GetScale().y * textH;

    texture->render(destRect);
}

int Renderer::getWidth()
{
    return texture->getW();
}

int Renderer::getHeight()
{
    return texture->getH();
}