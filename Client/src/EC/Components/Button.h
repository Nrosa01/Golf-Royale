#ifndef BUTTON_H
#define BUTTON_H

#include "../Component.h"
#include <functional>

using ButtonCallback = std::function<void()>;
class Texture;
class Transform;

class Button : public Component
{
public:
    Button(Texture *buttonImg, const char *text, std::string font, int fontSize, ButtonCallback callback);
    virtual ~Button();
    virtual void init();
    virtual void update(float deltaTime);
    virtual void render();
    bool isPressed();
    bool isMouseOver();
private:
    Texture *texture;
    const char *text;
    std::string font;
    ButtonCallback callback;
    float lerpAnimTime;
    float timer = 0.0f;
    Transform *transform;
    Vector2D initialScale;
    bool wasOverLastFrame;
    int fontSize;
    int initialFontSize;
};

#endif