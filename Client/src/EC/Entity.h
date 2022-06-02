#ifndef SDLEntityH
#define SDLEntityH

#include <unordered_map>
#include <iostream>
#include <list>
#include <vector>
#include <typeinfo>

class Transform;
class Component;
class SDLApp;

class Entity
{
public:
    Entity(int x, int y, SDLApp *app);
    Entity(SDLApp *app);
    ~Entity();

    void AddComponent(Component *component);
    void RemoveComponent(std::string name);

    Component *GetComponent(std::string name);
    void init();
    void update(float deltaTime);
    void lateUpdate(float deltaTime);
    void render();

    Transform *GetTransform();
    void SetGame(SDLApp *app);
    SDLApp *GetGame();

    // I cant define this in the cpp as it is a non specialized template method
    template <typename T>
    T *GetComponent(std::string name)
    {
        return dynamic_cast<T *>(GetComponent(name));
    }

    // THis is dangerous, might not work
    template <class T>
    T *GetComponent()
    {
        std::string n = typeid(T).name();
        return dynamic_cast<T *>(GetComponent(n));
    }

private:
    Transform *transform;
    SDLApp *app;
    std::unordered_map<std::string, Component *> components; // Used for fast getComponent
    std::vector<Component *> componentArray;
};

#endif