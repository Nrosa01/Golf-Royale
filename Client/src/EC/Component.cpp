#include "Component.h"
#include "../SDLUtils/SDLApp.h"
#include "Entity.h"

Component::Component(std::string cmpName) : cmpName(cmpName)  {}

Component::~Component() {}

void Component::init() {}

void Component::update(float deltaTime) {}

void Component::lateUpdate(float deltaTime) {}

void Component::render() {}

void Component::setOwner(Entity *owner) { ent = owner; }

Entity* Component::getOwner() { return ent; }

void Component::playSound(std::string soundName) { ent->GetGame()->playAudio(soundName); }

std::string Component::getName() { return cmpName; }

void Component::sendNetworkMessage(NetworkMessage &msg) { ent->GetGame()->sendNetworkMessage(msg); }

void Component::receiveNetworkMessage(NetworkMessage &msg) {}