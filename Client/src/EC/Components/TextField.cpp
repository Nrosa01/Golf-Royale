#include "TextField.h"
#include "Transform.h"
#include "../../SDLUtils/SDLApp.h"
#include "../../SDLUtils/Texture.h"
#include "../Entity.h"

TextField::TextField(Texture *buttonImg, std::string font, int fontSize, int maxLength) : Component(typeid(TextField).name()), texture(buttonImg), font(font), fontSize(fontSize), maxLength(maxLength)
{
    this->text = "";
    this->transform = nullptr;
    this->wasOverLastFrame = false;
    selected = false;
}

TextField::~TextField()
{
    delete textLine;
}

void TextField::init()
{
    this->transform = this->ent->getTransform();
    this->initialScale = transform->getScale();
    this->textLine = this->ent->getGame()->getTexture("textField");
    pulseSpeed = 0.75f;
    lineAlpha = 255;
    initialFontSize = fontSize;

    // Clone texture for text line
    this->textLine = textLine->getClone();
}

void TextField::update(float deltaTime)
{
    bool mouseButtonPressed = Input()->isMouseButtonPressed(0);

    if (mouseButtonPressed)
        selected = isMouseOver();

    if (selected && Input()->anyKeyWasPressed())
    {
        if (Input()->keyWasPressed(SDLK_BACKSPACE))
        {
            if (text.length() > 0)
            {
                text.pop_back();
                this->playSound("keyBack");
            }
        }
        else
        {
            char c = Input()->getLastKeyPressed();
            if (c >= 'a' && c <= 'z')
            {
                if (text.length() < maxLength)
                {
                    text += c;
                    this->playSound("key");
                }
            }
        }
    }

    if (selected)
        timer += deltaTime * pulseSpeed;
    else
        timer -= deltaTime * pulseSpeed;

    // Clamp timer between 0 and 1
    if (timer > 1.0f)
        timer = 0.0f;
    else if (timer < 0.0f)
        timer = 0.0f;
    lineAlpha = 255 * (sin(timer * 3.14f));

    textLine->setAlpha((int)this->lineAlpha);

    float scaleRatio = transform->getScale().magnitude() / initialScale.magnitude();
    fontSize = initialFontSize * scaleRatio;
}

void TextField::render()
{
    SDL_Rect destRect;
    int textW = texture->getW() * transform->getScale().x;
    int textH = texture->getH() * transform->getScale().y;
    destRect.x = transform->getPosition().getX() - textW / 2;
    destRect.y = transform->getPosition().getY() - textH / 2;
    destRect.w = textW;
    destRect.h = textH;

    texture->render(destRect);
    textLine->render(destRect);

    if (text.size() == 0)
        return;

    int textPosX = transform->getPosition().getX();
    int textPosY = transform->getPosition().getY();
    SDL_Color defaultColor = {255, 255, 255, 255};
    this->ent->getGame()->renderText(textPosX, textPosY, text.c_str(), font, fontSize, defaultColor);
}

bool TextField::isPressed()
{
    bool mouseButtonPressed = Input()->isMouseButtonPressed(0);
    bool mouseOver = isMouseOver();

    return mouseButtonPressed && mouseOver;
}

bool TextField::isMouseOver()
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

uint TextField::getMaxLength()
{
    return maxLength;
}

std::string TextField::getText()
{
    return text;
}

void TextField::setText(std::string text)
{
    this->text = text;
}