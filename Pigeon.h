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


struct Pigeon : Component
{
private:

    enum PigeonState{MOVING, RESTING};
    PigeonState m_state;
    Timer m_restTimer;
    Vec2 m_destination;
    Vec2 m_speedVec;
    float m_restTime;

    Sprite2* m_sptIdleLeft;
    Sprite2* m_sptIdleRight;
    Sprite2* m_sptMovingLeft;
    Sprite2* m_sptMovingRight;

    enum Direction {LEFT, RIGHT};
    Direction m_direction;
    void SetDirection();

    void CheckPlayerHitboxCollision();

public:

    int m_hp;
    std::string type = "Pigeon";
    Collider* m_collider; 

    Pigeon(GameObject& associated, float restTime);
    ~Pigeon();

    void Start();
    void Update(float dt);
    void Render();
    bool Is(std::string type);
    void NotifyCollision(GameObject& other);
};

