#include "Renderer.h"
#include "../Entity.h"
#include "Transform.h"
#include "../../SDLUtils/Texture.h"
#include "../../SDLUtils/SDLApp.h"

Renderer::Renderer(Texture *texture) : Component(typeid(Renderer).name()), transform(nullptr), texture(texture){};

Renderer::~Renderer(){};

void Renderer::init()
{
    transform = this->ent->getComponent<Transform>();

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
    int posx = transform->getPosition().x;
    int posy = transform->getPosition().y;
    this->ent->getGame()->renderText(posx, posy, std::to_string(posx).c_str(), "toonFont", 20, {255, 0, 0});
    this->ent->getGame()->renderText(posx, posy + 20, std::to_string(posx).c_str(), "toonFont", 20, {0, 0, 0});
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
    int textW = texture->getW() * transform->getScale().x;
    int textH = texture->getH() * transform->getScale().y;
    destRect.x = transform->getPosition().getX();
    destRect.y = transform->getPosition().getY();
    destRect.w = textW;
    destRect.h = textH;

    return destRect;
}

SDL_Rect Renderer::getDestRectCentered()
{
    SDL_Rect destRect;
    int textW = texture->getW() * transform->getScale().x;
    int textH = texture->getH() * transform->getScale().y;
    destRect.x = transform->getPosition().getX() - textW / 2;
    destRect.y = transform->getPosition().getY() - textH / 2;
    destRect.w = textW;
    destRect.h = textH;

    return destRect;
}


SDL_Rect Renderer::getDestRectAt(Vector2D position)
{
    SDL_Rect destRect;
    int textW = texture->getW() * transform->getScale().x;
    int textH = texture->getH() * transform->getScale().y;
    destRect.x = position.getX();
    destRect.y = position.getY();
    destRect.w = textW;
    destRect.h = textH;

    return destRect;
}