#include "Component.h"

Component::Component(std::string cmpName) : cmpName(cmpName) {}

Component::~Component() {}

void Component::init() {}

void Component::update(float deltaTime) {}

void Component::render() {}

void Component::setOwner(Entity *owner) { ent = owner; }

std::string Component::getName() { return cmpName; }