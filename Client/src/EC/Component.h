#ifndef COMPONENT_H
#define COMPONENT_H

class Component
{
public:
    Component(std::string cmpName) : cmpName(cmpName) {};
    virtual ~Component() {};
    virtual void update(float deltaTime) = 0;
    virtual void render() = 0;
    std::string GetName() { return cmpName; }
private:
std::string cmpName;
};

#endif