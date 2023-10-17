#pragma once

#include "Vec2.h"
#include "Component.h"
#include "Sprite2.h"

#define PLAYER_SPEED 100

struct Player : Component
{
    Vec2 m_speedVec;
    bool m_flip;
    
    Sprite2* m_spriteIdle;
    Sprite2* m_spriteWalking;

    Player(GameObject& associated);
    Player();
    void Start();
    void Update(float dt);
    void Render();
    bool Is(std::string);
    void NotifyCollision(GameObject& other);
};
