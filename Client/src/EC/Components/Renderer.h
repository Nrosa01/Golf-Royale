#ifndef ENT_RENDERER_H
#define ENT_RENDERER_H

#include "../Component.h"

class Texture;
class Transform;

class Renderer : public Component
{
public:
    Renderer(Texture* texture);
    virtual ~Renderer();
    virtual void init();
    virtual void render();
private:
Transform* transform;
Texture* texture;
};

#endif