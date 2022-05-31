#include "Button.h"
#include "Transform.h"
#include "../../SDLUtils/SDLApp.h"
#include "../../SDLUtils/Texture.h"
#include "../Entity.h"

Button::Button(Texture *buttonImg, const char *text, std::string font, ButtonCallback callback) : Component("Button"), texture(buttonImg),
                                                                                                  text(text), font(font), callback(callback), lerpAnimTime(0.1f) {}

Button::~Button() {}

void Button::init()
{
    transform = this->ent->GetTransform();
    initialScale = transform->GetScale();
    wasOverLastFrame = false;
}

void Button::update(float deltaTime)
{
    if (isPressed() && callback != nullptr)
    {
        this->playSound("button");
        callback();
    }

    if (isMouseOver())
    {
        // Lerp scale from current Scale to 1.1f
        timer += deltaTime;
        if (timer > lerpAnimTime)
            timer = lerpAnimTime;

        if (!wasOverLastFrame)
        {
            wasOverLastFrame = true;
            this->playSound("swoosh");
        }
    }
    else
    {
        // Lerp scale from current Scale to 1.0f
        timer -= deltaTime;
        if (timer < 0.0f)
            timer = 0.0f;

        wasOverLastFrame = false;
    }

    float scaleX = initialScale.x + (timer / lerpAnimTime) * 0.1f;
    float scaleY = initialScale.y + (timer / lerpAnimTime) * 0.1f;
    transform->GetScale() = Vector2D(scaleX, scaleY);
}

void Button::render()
{
    SDL_Rect destRect;
    int textW = texture->getW() * transform->GetScale().x;
    int textH = texture->getH() * transform->GetScale().y;
    destRect.x = transform->GetPosition().getX() - textW / 2;
    destRect.y = transform->GetPosition().getY() - textH / 2;
    destRect.w = textW;
    destRect.h = textH;

    texture->render(destRect);

    if (text != nullptr)
    {
        int textPosX = transform->GetPosition().getX();
        int textPosY = transform->GetPosition().getY();
        SDL_Color hoverColor = {255, 255, 255, 255};
        SDL_Color defaultColor = {255, 255, 255, 175};
        SDL_Color color = isMouseOver() ? hoverColor : defaultColor;
        this->ent->GetGame()->renderText(textPosX, textPosY, text, font, color);
    }
}

bool Button::isPressed()
{
    bool mouseButtonPressed = Input()->IsMouseButtonPressed(0);
    bool mouseOver = isMouseOver();

    return mouseButtonPressed && mouseOver;
}

bool Button::isMouseOver()
{
    Vector2D mousePos = Input()->GetMousePosition();

    // Check if mousePos is inside the button
    int textW = texture->getW() * transform->GetScale().x;
    int textH = texture->getH() * transform->GetScale().y;
    if (mousePos.getX() > transform->GetPosition().getX() - textW / 2 && mousePos.getX() < transform->GetPosition().getX() + textW / 2 &&
        mousePos.getY() > transform->GetPosition().getY() - textH / 2 && mousePos.getY() < transform->GetPosition().getY() + textH / 2)
    {
        return true;
    }
    else
        return false;
}