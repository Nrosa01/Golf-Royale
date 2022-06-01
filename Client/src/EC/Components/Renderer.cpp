#include "Renderer.h"
#include "../Entity.h"
#include "Transform.h"
#include "../../SDLUtils/Texture.h"
#include <SDL2/SDL.h>

Renderer::Renderer(Texture *texture) : Component(typeid(Renderer).name()), transform(nullptr), texture(texture){};

Renderer::~Renderer(){};

void Renderer::init()
{
    transform = this->ent->GetComponent<Transform>();

    if (transform == nullptr)
    {
        std::cout << "Renderer::init() - ERROR: Entity does not have a Transform component!" << std::endl;
        return;
    }
    
}

void Renderer::render()
{
    SDL_Rect destRect;
    int textW = texture->getW() * transform->GetScale().x;
    int textH = texture->getH() * transform->GetScale().y;
    destRect.x = transform->GetPosition().getX() - textW / 2;
    destRect.y = transform->GetPosition().getY() - textH / 2;
    destRect.w = textW;
    destRect.h = textH;

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