#pragma once

#include "Component.h"
#include "Sprite2.h"

struct Wall : Component
{
    Wall(GameObject& associated, Vec2 dimensions, Vec2 pos);
    ~Wall();
    void Start();
    void Update(float dt);
    void Render();
    bool Is(std::string);
    void NotifyCollision(GameObject& other);
};

