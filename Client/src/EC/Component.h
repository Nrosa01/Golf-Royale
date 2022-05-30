#ifndef COMPONENT_H
#define COMPONENT_H

class Entity;

class Component
{
public:
    Component(std::string cmpName) : cmpName(cmpName){};
    virtual ~Component(){};
    virtual void init() {};
    virtual void update(float deltaTime) {};
    virtual void render() {};
    std::string GetName() { return cmpName; }
    void SetOwner(Entity *owner) { this->ent = owner; }

protected:
    Entity *ent;

private:
    std::string cmpName;
};

#endif