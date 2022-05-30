#ifndef SDLEntityH
#define SDLEntityH

#include <unordered_map>
#include <iostream>
#include <list>

class Transform;
class Component;

class Entity
{
public:
    Entity(int x, int y);
    Entity();
    ~Entity();

    void AddComponent(Component *component);
    void RemoveComponent(std::string name);
    template <typename T>
    T *GetComponent(std::string name);
    void update(float deltaTime);
    void render();

    Transform *GetTransform();

private:
    Transform *transform;
    std::unordered_map<std::string, Component *> components;
    std::list<Component *> unitializedComponents;
};

#endif