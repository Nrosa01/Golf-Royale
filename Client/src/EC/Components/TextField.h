#ifndef TEXTFIELD_H
#define TEXTFIELD_H 

#include "../Component.h"

class Texture;
class Transform;

class TextField : public Component
{
public:
    TextField(Texture *buttonImg, std::string font, int maxLength = 4);
    virtual ~TextField();
    virtual void init();
    virtual void update(float deltaTime);
    virtual void render();
    bool isPressed();
    bool isMouseOver();
private:
    Texture *texture;
    std::string font;
    uint maxLength;
    Texture *textLine;
    std::string text;
    Transform *transform;
    Vector2D initialScale;
    bool wasOverLastFrame;
    bool selected;
    float lineAlpha;
    float pulseSpeed;
    float timer;
};

#endif