#include "Renderer.h"
#include "../Entity.h"
#include "Transform.h"
#include "../../SDLUtils/Texture.h"
#include "../../SDLUtils/SDLApp.h"

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
    texture->render(getDestRectCentered());

    return;
    // Render text with position, used for debug
    int posx = transform->GetPosition().x;
    int posy = transform->GetPosition().y;
    this->ent->GetGame()->renderText(posx, posy, std::to_string(posx).c_str(), "toonFont", 20, {255, 0, 0});
    this->ent->GetGame()->renderText(posx, posy + 20, std::to_string(posx).c_str(), "toonFont", 20, {0, 0, 0});
}

int Renderer::getWidth()
{
    return texture->getW();
}

int Renderer::getHeight()
{
    return texture->getH();
}

SDL_Rect Renderer::getDestRect()
{
    SDL_Rect destRect;
    int textW = texture->getW() * transform->GetScale().x;
    int textH = texture->getH() * transform->GetScale().y;
    destRect.x = transform->GetPosition().getX();
    destRect.y = transform->GetPosition().getY();
    destRect.w = textW;
    destRect.h = textH;

    return destRect;
}

SDL_Rect Renderer::getDestRectCentered()
{
    SDL_Rect destRect;
    int textW = texture->getW() * transform->GetScale().x;
    int textH = texture->getH() * transform->GetScale().y;
    destRect.x = transform->GetPosition().getX() - textW / 2;
    destRect.y = transform->GetPosition().getY() - textH / 2;
    destRect.w = textW;
    destRect.h = textH;

    return destRect;
}


SDL_Rect Renderer::getDestRectAt(Vector2D position)
{
    SDL_Rect destRect;
    int textW = texture->getW() * transform->GetScale().x;
    int textH = texture->getH() * transform->GetScale().y;
    destRect.x = position.getX();
    destRect.y = position.getY();
    destRect.w = textW;
    destRect.h = textH;

    return destRect;
}