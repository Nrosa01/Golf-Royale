#include "Entity.h"
#include "../MathUtils/Vector2D.h"
#include "Component.h"
#include "Components/Transform.h"
#include "../SDLUtils/SDLApp.h"
#include <string>

Entity::Entity(int x, int y, SDLApp *game)
{
    transform = new Transform(Vector2D(x, y), 1.0f);
    AddComponent(transform);
    SetGame(game);
}

Entity::Entity(SDLApp *game)
{
    transform = new Transform(Vector2D(0, 0), 1.0f);
    AddComponent(transform);
    SetGame(game);
}

Entity::~Entity()
{
    for (auto component : components)
        delete component.second;
}

void Entity::AddComponent(Component *component)
{
    components[component->getName()] = component;
    component->setOwner(this);
    this->unitializedComponents.push_back(component);
    this->componentArray.push_back(component);
}

void Entity::RemoveComponent(std::string name)
{
    // Delete from array
    for (auto it = componentArray.begin(); it != componentArray.end(); it++)
    {
        if ((*it)->getName() == name)
        {
            componentArray.erase(it);
            break;
        }
    }

    // Find component
    auto component = components.find(name);
    if (component != components.end())
    {
        // Delete component
        delete component->second;
        // Remove from map
        components.erase(component);
    }
}

template <typename T>
T *Entity::GetComponent(std::string name)
{
    return dynamic_cast<T *>(GetComponent(name));
}

Component *Entity::GetComponent(std::string name)
{
    // Find component
    auto component = components.find(name);
    if (component != components.end())
        return component->second;
    else
        return nullptr;
}

void Entity::update(float deltaTime)
{
    // Init unitialized components
    for (auto component : unitializedComponents)
        component->init();

    this->unitializedComponents.clear();

    for (auto component : componentArray)
        component->update(deltaTime);
}

void Entity::render()
{
    for (auto component : componentArray)
        component->render();
}

Transform *Entity::GetTransform()
{
    return transform;
}

void Entity::SetGame(SDLApp *game)
{
    this->game = game;
}

SDLApp *Entity::GetGame()
{
    return game;
}