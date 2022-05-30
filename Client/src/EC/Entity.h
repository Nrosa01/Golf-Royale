#ifndef SDLEntityH
#define SDLEntityH

#include <unordered_map>
#include <iostream>
#include <list>

class Transform;
class Component;
class SDLApp;

class Entity
{
public:
    Entity(int x, int y, SDLApp* game);
    Entity(SDLApp* game);
    ~Entity();

    void AddComponent(Component *component);
    void RemoveComponent(std::string name);
    template <typename T>
    T *GetComponent(std::string name);
    void update(float deltaTime);
    void render();

    Transform *GetTransform();
    void SetGame(SDLApp *game);
    SDLApp* GetGame();
private:
    Transform *transform;
    SDLApp* game;
    std::unordered_map<std::string, Component *> components;
    std::list<Component *> unitializedComponents;
};

#endif