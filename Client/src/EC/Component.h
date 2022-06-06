#ifndef ENT_COMPONENT_H
#define ENT_COMPONENT_H

#include <string>
#include "../SDLUtils/InputSytem.h"
#include <typeinfo>
#include "../Network/NetworkMessage.h"

class Entity;
class Transform;

class Component
{
public:
    Component(std::string cmpName);
    virtual ~Component();
    virtual void init();
    virtual void update(float deltaTime);
    virtual void lateUpdate(float deltaTime);
	virtual void receiveNetworkMessage(NetworkMessage* msg);
    virtual void render();
    std::string getName();
    void setOwner(Entity *owner);
    Entity *getOwner();

protected:
    void playSound(std::string soundName);
    void sendNetworkMessage(NetworkMessage &msg);
    Entity *ent;
    Transform* transform;

private:
    std::string cmpName;
};

#endif