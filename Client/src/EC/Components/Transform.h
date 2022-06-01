#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "../Component.h"
#include "../../MathUtils/Vector2D.h"

class Transform : public Component
{
public:
    Transform() : Component(typeid(Transform).name()), position(Vector2D(0,0)), scale(Vector2D(1,1)) {};
    Transform(Vector2D position, float scale) : Component(typeid(Transform).name()), position(position), scale(Vector2D(scale, scale)) {};
    virtual ~Transform() {};

    Vector2D& GetPosition() { return position; }
    Vector2D& GetScale() { return scale; }
private:
    Vector2D position;
    Vector2D scale;
};

#endif