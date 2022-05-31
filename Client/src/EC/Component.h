#ifndef ENT_COMPONENT_H
#define ENT_COMPONENT_H

#include <string>
#include "../SDLUtils/InputSytem.h"

class Entity;

class Component
{
public:
    Component(std::string cmpName);
    virtual ~Component();
    virtual void init();
    virtual void update(float deltaTime);
    virtual void lateUpdate(float deltaTime);
    virtual void render();
    std::string getName();
    void setOwner(Entity *owner);
    void playSound(std::string soundName);

protected:
    Entity *ent;

private:
    std::string cmpName;
};

#endif