#ifndef ENT_COMPONENT_H
#define ENT_COMPONENT_H

#include <string>
class Entity;

class Component
{
public:
    Component(std::string cmpName);
    virtual ~Component();
    virtual void init();
    virtual void update(float deltaTime);
    virtual void render();
    std::string getName();
    void setOwner(Entity *owner);

protected:
    Entity *ent;

private:
    std::string cmpName;
};

#endif