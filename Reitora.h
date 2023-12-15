#pragma once

#include <vector>
#include <string>
#include <queue>
#include <memory>
#include "Sprite2.h"
#include "Component.h"
#include "Vec2.h"
#include "GameObject.h"
#include "Timer.h"
#include "Collider.h"

struct Reitora : Component
{
    enum ReitoraState{ATTACKED, RESTING};
    ReitoraState m_state;
    Timer m_timer;

    Sprite2* m_sptIdle;
    Sprite2* m_sptUnderAttack;

    std::string type = "Reitora";
    Collider* m_collider; 

    Reitora(GameObject& associated);
    ~Reitora();

    void Start();
    void Update(float dt);
    void Render();
    bool Is(std::string type);
    void NotifyCollision(GameObject& other);
};


