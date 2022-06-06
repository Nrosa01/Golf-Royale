#include "TextRenderer.h"
#include "Transform.h"
#include "../../SDLUtils/SDLApp.h"
#include "../../SDLUtils/Texture.h"
#include "../Entity.h"

TextRenderer::TextRenderer(std::string text, std::string font, int fontSize, SDL_Color textColor, Vector2D offset) : Component(typeid(TextRenderer).name()), text(text),
                                                                                                                     font(font), fontSize(fontSize), textColor(textColor), offset(offset) {}
TextRenderer::~TextRenderer() {}

void TextRenderer::init()
{
    Transform *transform = this->ent->getTransform();
    initialScale = transform->getScale();
}

void TextRenderer::render()
{
    if (text.empty())
        return;

    Transform *transform = this->ent->getTransform();
    float scaleRatio = transform->getScale().magnitude() / initialScale.magnitude();

    Vector2D pos = transform->getPosition() + offset;
    this->ent->getGame()->renderText(pos.x, pos.y, text.c_str(), font, fontSize * scaleRatio, textColor);
}

void TextRenderer::setText(const char *text)
{
    this->text = text;
}

void TextRenderer::setText(std::string text)
{
    this->text = text.c_str();
}