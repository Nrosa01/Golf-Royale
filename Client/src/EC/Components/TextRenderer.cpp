#include "TextRenderer.h"
#include "Transform.h"
#include "../../SDLUtils/SDLApp.h"
#include "../../SDLUtils/Texture.h"
#include "../Entity.h"

TextRenderer::TextRenderer(const char *text, std::string font, int fontSize, SDL_Color textColor, Vector2D offset) : Component(typeid(TextRenderer).name()), text(text),
                                                                                                                                 font(font), fontSize(fontSize), textColor(textColor), offset(offset) {}
TextRenderer::~TextRenderer() {}

void TextRenderer::init()
{
    Transform *transform = this->ent->GetTransform();
    initialScale = transform->GetScale();
}

void TextRenderer::render()
{
    Transform *transform = this->ent->GetTransform();
    float scaleRatio = transform->GetScale().Magnitude() / initialScale.Magnitude();

    Vector2D pos = transform->GetPosition() + offset;
    this->ent->GetGame()->renderText(pos.x, pos.y, text, font, fontSize * scaleRatio, textColor);
}