#pragma once

#include "Rect.h"
#include "Vec2.h"
#include <vector>
#include <memory>
#include <string>

//forward declaration
struct Component;

struct GameObject
{
private: 
    std::vector<std::unique_ptr<Component>> m_components;
    bool m_isDead;
public: 
    bool m_started;

    Rect m_box;
    Vec2 m_pos;
    float m_angleDeg;

    GameObject();
    ~GameObject();

    void Start();
    void Update(float dt);
    void Render();
    bool IsDead();
    void RequestDelete();
    void AddComponent(Component* cpt);
    void RemoveComponent(Component* cpt);
    Component* GetComponent(std::string cpt);
    Vec2 GetCenter();

    void NotifyCollision(GameObject& other);
};
