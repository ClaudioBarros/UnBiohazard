#pragma once

#include "Vec2.h"
#include "GameObject.h"
#include "Component.h"
#include "Helper.h"
#include <string>

struct Collider : Component
{
private:
    Vec2 m_scale;
    Vec2 m_offset;
public:
    Rect m_box;

    Collider(GameObject& associated,
             Vec2 scale = Vec2(1.0f, 1.0f),
             Vec2 offset = Vec2(0.0f, 0.0f));
    
    void Start();
    void Update(float dt);
    void Render();
    bool Is(std::string type);

    void SetScale(Vec2 scale);
    void SetOffset(Vec2 offset);
    static void solveWallCollision(Helper::Direction directionX,
                                   Helper::Direction directionY,
                                   GameObject *associated, 
                                   Collider* playerCollider, 
                                   Collider* wall, 
                                   Vec2 speed);
};
