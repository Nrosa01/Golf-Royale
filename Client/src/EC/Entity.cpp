#include "Entity.h"
#include "../MathUtils/Vector2D.h"
#include "Component.h"
#include "Components/Transform.h"
#include "../SDLUtils/SDLApp.h"
#include "../Network/NetworkMessage.h"
#include <string>

Entity::Entity(int x, int y, SDLApp *app)
{
    transform = new Transform(Vector2D(x, y), 1.0f);
    addComponent(transform);
    setGame(app);
}

Entity::Entity(SDLApp *app)
{
    transform = new Transform(Vector2D(0, 0), 1.0f);
    addComponent(transform);
    setGame(app);
}

Entity::~Entity()
{
    for (auto component : components)
        delete component.second;
}

void Entity::addComponent(Component *component)
{
    components[component->getName()] = component;
    component->setOwner(this);
    this->componentArray.push_back(component);
}

void Entity::removeComponent(std::string name)
{
    if (name == transform->getName())
    {
        std::cerr << "Cannot remove transform component" << std::endl;
        return;
    }

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

Component *Entity::getComponent(std::string name)
{
    // Find component
    auto component = components.find(name);
    if (component != components.end())
        return component->second;
    else
        return nullptr;
}

void Entity::init()
{
    for (auto component : componentArray)
        component->init();
}

void Entity::update(float deltaTime)
{
    for (auto component : componentArray)
        component->update(deltaTime);
}

void Entity::lateUpdate(float deltaTime)
{
    for (auto component : componentArray)
        component->lateUpdate(deltaTime);
}

void Entity::render()
{
    for (auto component : componentArray)
        component->render();
}

void Entity::receiveNetworkMessage(NetworkMessage *msg)
{
    for (auto component : componentArray)
        component->receiveNetworkMessage(msg);
}

Transform *Entity::getTransform()
{
    return transform;
}

void Entity::setGame(SDLApp *app)
{
    this->app = app;
}

SDLApp *Entity::getGame()
{
    return app;
}