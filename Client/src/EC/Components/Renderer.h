#ifndef RENDERER_H
#define RENDERER_H

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