#ifndef TEXTFIELD_H
#define TEXTFIELD_H 

#include "../Component.h"

class Texture;
class Transform;

class TextField : public Component
{
public:
    TextField(Texture *buttonImg, std::string font, int fontSize, int maxLength = 4);
    virtual ~TextField();
    virtual void init();
    virtual void update(float deltaTime);
    virtual void render();
    std::string getText();
    void setText(std::string text);
    bool isPressed();
    bool isMouseOver();
    uint getMaxLength();
private:
    Texture *texture;
    std::string font;
    int fontSize;
    int initialFontSize;
    uint maxLength;
    Texture *textLine;
    std::string text;
    Vector2D initialScale;
    bool wasOverLastFrame;
    bool selected;
    float lineAlpha;
    float pulseSpeed;
    float timer;
};

#endif