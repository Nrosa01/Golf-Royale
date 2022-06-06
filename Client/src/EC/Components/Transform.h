#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "../Component.h"
#include "../../MathUtils/Vector2D.h"

class Transform : public Component
{
public:
    Transform() : Component(typeid(Transform).name()), _position(Vector2D(0,0)), _scale(Vector2D(1,1)), position(_position), scale(_scale) {};
    Transform(Vector2D position, float scale) : Component(typeid(Transform).name()), _position(position), _scale(Vector2D(scale, scale)), position(_position), scale(_scale) {};
    virtual ~Transform() {};

    Vector2D& getPosition() { return _position; }
    Vector2D& getScale() { return _scale; }
    float& getRotation() { return rotation; }
    Vector2D& position;
    Vector2D& scale;
private:
    Vector2D _position;
    Vector2D _scale;
    float rotation;
};

#endif