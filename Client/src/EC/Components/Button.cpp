#include "Button.h"
#include "Transform.h"
#include "../../SDLUtils/SDLApp.h"
#include "../../SDLUtils/Texture.h"
#include "../Entity.h"

Button::Button(Texture *buttonImg, const char *text, std::string font, int fontSize, ButtonCallback callback) : Component(typeid(Button).name()), texture(buttonImg),
                                                                                                                text(text), font(font), callback(callback), lerpAnimTime(0.1f), fontSize(fontSize) {}

Button::~Button() {}

void Button::init()
{
    initialScale = transform->getScale();
    wasOverLastFrame = false;
    initialFontSize = fontSize;
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
        // lerp scale from current Scale to 1.1f
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
        // lerp scale from current Scale to 1.0f
        timer -= deltaTime;
        if (timer < 0.0f)
            timer = 0.0f;

        wasOverLastFrame = false;
    }

    float scaleX = initialScale.x + (timer / lerpAnimTime) * 0.1f;
    float scaleY = initialScale.y + (timer / lerpAnimTime) * 0.1f;
    float scaleRatio = transform->getScale().magnitude() / initialScale.magnitude();

    fontSize = initialFontSize + (timer / lerpAnimTime) * 20.0f;
    fontSize *= scaleRatio;
    transform->getScale() = Vector2D(scaleX, scaleY);
}

void Button::render()
{
    SDL_Rect destRect;
    int textW = texture->getW() * transform->getScale().x;
    int textH = texture->getH() * transform->getScale().y;
    destRect.x = transform->getPosition().getX() - textW / 2;
    destRect.y = transform->getPosition().getY() - textH / 2;
    destRect.w = textW;
    destRect.h = textH;

    texture->render(destRect);

    if (text != nullptr)
    {
        int textPosX = transform->getPosition().getX();
        int textPosY = transform->getPosition().getY();
        SDL_Color hoverColor = {255, 255, 255, 255};
        SDL_Color defaultColor = {255, 255, 255, 175};
        SDL_Color color = isMouseOver() ? hoverColor : defaultColor;
        this->ent->getGame()->renderText(textPosX, textPosY, text, font, fontSize, color);
    }
}

bool Button::isPressed()
{
    bool mouseButtonPressed = Input()->isMouseButtonPressed(0);
    bool mouseOver = isMouseOver();

    return mouseButtonPressed && mouseOver;
}

bool Button::isMouseOver()
{
    Vector2D mousePos = Input()->getMousePosition();

    // Check if mousePos is inside the button
    int textW = texture->getW() * transform->getScale().x;
    int textH = texture->getH() * transform->getScale().y;
    if (mousePos.getX() > transform->getPosition().getX() - textW / 2 && mousePos.getX() < transform->getPosition().getX() + textW / 2 &&
        mousePos.getY() > transform->getPosition().getY() - textH / 2 && mousePos.getY() < transform->getPosition().getY() + textH / 2)
    {
        return true;
    }
    else
        return false;
}