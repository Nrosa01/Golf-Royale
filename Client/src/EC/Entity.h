#ifndef SDLEntityH
#define SDLEntityH

#include <unordered_map>
#include <iostream>
#include <list>
#include <vector>

class Transform;
class Component;
class SDLApp;

class Entity
{
public:
    Entity(int x, int y, SDLApp* app);
    Entity(SDLApp* app);
    ~Entity();

    void AddComponent(Component *component);
    void RemoveComponent(std::string name);
    template <typename T>
    T *GetComponent(std::string name);
    Component *GetComponent(std::string name);
    void update(float deltaTime);
    void lateUpdate(float deltaTime);
    void render();

    Transform *GetTransform();
    void SetGame(SDLApp *app);
    SDLApp* GetGame();
private:
    Transform *transform;
    SDLApp* app;
    std::unordered_map<std::string, Component *> components; //Used for fast getComponent
    std::vector<Component *> componentArray;
    std::list<Component *> unitializedComponents;
};

#endif