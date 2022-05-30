#ifndef SDLEntityH
#define SDLEntityH

#include <unordered_map>
#include "../MathUtils/Vector2D.h"
#include "Component.h"
#include "Components/Transform.h"
#include <iostream>
#include <list>

class Entity
{
public:
    Entity(int x, int y)
    {
        transform = new Transform(Vector2D(x, y), 1.0f);
        AddComponent(transform);
    };

    Entity()
    {
        transform = new Transform(Vector2D(0, 0), 1.0f);
        AddComponent(transform);
    };

    ~Entity()
    {
        for (auto &component : components)
            delete component.second;
    };

    void AddComponent(Component *component)
    {
        components[component->GetName()] = component;
        component->SetOwner(this);
        this->unitializedComponents.push_back(component);
    };

    void RemoveComponent(std::string name)
    {
        // Find component
        auto it = components.find(name);
        if (it != components.end())
        {
            // Delete component
            delete it->second;
            // Remove from map
            components.erase(it);
        }
    };

    template <typename T>
    T *GetComponent(std::string name)
    {
        auto it = components.find(name);
        if (it != components.end())
            return static_cast<T *>(it->second);
        return nullptr;
    };

    void update(float deltaTime)
    {
        for (auto &component : unitializedComponents)
            component->init();

        this->unitializedComponents.clear();

        for (auto &component : components)
            component.second->update(deltaTime);
    };

    void render()
    {
        for (auto &component : components)
            component.second->render();
    };

    Transform *GetTransform()
    {
        return transform;
    };

private:
    Transform *transform;
    std::unordered_map<std::string, Component *> components;
    std::list<Component *> unitializedComponents;
};

#endif