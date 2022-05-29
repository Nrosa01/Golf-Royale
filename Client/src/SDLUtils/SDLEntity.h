#ifndef SDLEntityH
#define SDLEntityH

#include "Vector2D.h"

class SDLEntity
{
public:
    SDLEntity(int x, int y, int width, int height);

    virtual void update(float deltaTime) = 0;
    virtual void render() = 0;

protected:
    Vector2D position;
    Vector2D size;
    float scale;
};

#endif