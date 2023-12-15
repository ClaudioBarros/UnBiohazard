#pragma once

#include "Component.h"
#include "Sprite2.h"
#include "Collider.h"

struct Hitbox : Component
{
    Collider* m_collider;
    Hitbox(GameObject& associated,Vec2 pos, Vec2 dimensions, Vec2 scale, Vec2 offset);
    ~Hitbox();
    void Start();
    void Update(float dt);
    void Render();
    bool Is(std::string);
    void NotifyCollision(GameObject& other);
};

