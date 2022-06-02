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
    Transform *transform = this->ent->GetTransform();
    initialScale = transform->GetScale();
}

void TextRenderer::render()
{
    if (text.empty())
        return;

    Transform *transform = this->ent->GetTransform();
    float scaleRatio = transform->GetScale().Magnitude() / initialScale.Magnitude();

    Vector2D pos = transform->GetPosition() + offset;
    this->ent->GetGame()->renderText(pos.x, pos.y, text.c_str(), font, fontSize * scaleRatio, textColor);
}

void TextRenderer::setText(const char *text)
{
    this->text = text;
}

void TextRenderer::setText(std::string text)
{
    this->text = text.c_str();
}