#pragma once

#include <string> 

struct GameObject;

struct Component
{
public:
    GameObject& m_associated;

    bool m_started = false;

    Component(GameObject& associated) : m_associated(associated) {}
    virtual ~Component(){};

    virtual void Start() = 0;
    virtual void Update(float dt) = 0;
    virtual void Render() = 0;
    virtual bool Is(std::string type) = 0;
    virtual void NotifyCollision(GameObject& other){}
};
