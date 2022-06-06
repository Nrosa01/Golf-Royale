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
class NetworkMessage;

class Entity
{
public:
    Entity(int x, int y, SDLApp *app);
    Entity(SDLApp *app);
    ~Entity();

    void aAddComponent(Component *component);
    void removeComponent(std::string name);

    Component *getComponent(std::string name);
    void init();
    void update(float deltaTime);
    void lateUpdate(float deltaTime);
    void render();
	void receiveNetworkMessage(NetworkMessage* msg);

    Transform *getTransform();
    void setGame(SDLApp *app);
    SDLApp *getGame();

    // This is dangerous, might not work
    template <class T>
    T *getComponent()
    {
        std::string n = typeid(T).name();
        return dynamic_cast<T *>(getComponent(n));
    }

private:
    Transform *transform;
    SDLApp *app;
    std::unordered_map<std::string, Component *> components; // Used for fast getComponent
    std::vector<Component *> componentArray;
};

#endif