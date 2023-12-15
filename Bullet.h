#pragma once

#include "Component.h"
#include "GameObject.h"
#include "Collider.h"
#include "Vec2.h"

struct Bullet : Component
{
private:
    float m_speed;
    Vec2 m_speed_vec;
    float m_distanceLeft;
    int m_damage;
    Collider* m_collider;
    
public:
    Bullet(GameObject& associated, 
           bool targetsPlayer,
           float angle,
           float speed,
           int damage,
           float maxDistance,
           unsigned frameCount,
           float frameTime,
           std::string sprite);
    ~Bullet(){}
    void Start();
    void Update(float dt);
    void Render();
    bool Is(std::string type);
    int GetDamage();
    void NotifyCollision(GameObject& other);

    void CheckHitboxCollision();

    bool m_targetsPlayer;
};

