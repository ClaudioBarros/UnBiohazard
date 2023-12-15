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

struct Sarue : Component
{
private:

    enum SarueState{MOVING, RESTING, SHOOTING};
    SarueState m_state;
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

    void Shoot(Vec2 target);

public:

    static Sarue* sarue;

    int m_hp;
    std::string type = "Sarue";
    Collider* m_collider; 

    Sarue(GameObject& associated, float restTime);
    ~Sarue();

    void Start();
    void Update(float dt);
    void Render();
    bool Is(std::string type);
    void NotifyCollision(GameObject& other);
};


