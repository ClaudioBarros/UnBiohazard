#include "Bullet.h"
#include "Sprite.h"
#include "Helper.h"
#include "Rect.h"
#include "Collider.h"
#include "Player.h"
#include "Sarue.h"
#include "Pigeon.h"

Bullet::Bullet(GameObject& associated, 
               bool targetsPlayer,
               float angle,
               float speed,
               int damage,
               float maxDistance,
               unsigned frameCount,
               float frameTime,
               std::string sprite) : Component(associated)
{
    Sprite* s = new Sprite(associated, sprite, frameCount, frameTime);
    m_collider = new Collider(associated);
    m_associated.AddComponent(s);
    m_associated.AddComponent(m_collider);
    m_associated.m_box = Rect(0.0f, 0.0f, s->GetWidth(), s->GetHeight());
    m_speed = speed;
    m_speed_vec = speed * Vec2(cos(angle), sin(angle)); 
    m_distanceLeft = maxDistance;
    m_damage = damage;
    m_associated.m_angleDeg = RAD2DEG(angle);
    m_targetsPlayer = targetsPlayer;
}

void Bullet::CheckHitboxCollision()
{
    Player* p = Player::player;
    if(m_targetsPlayer && p != nullptr)
    {
        if(IsColliding(m_collider->m_box, Player::player->m_hitbox->m_collider->m_box, 0.0f, 0.0f))
        {
            {
                p->m_hp = p->m_hp - 100;
            }
            printf("Collision: Bullet - Player \n");

            m_associated.RequestDelete();
        }
        return;
    }

    Sarue* s = Sarue::sarue;
    if(!s) return;
    if(!m_targetsPlayer)
    {
        if(IsColliding(m_collider->m_box, Sarue::sarue->m_collider->m_box, 0.0f, 0.0f))
        {
            {
                s->m_hp = s->m_hp - 100;
            }
            printf("Collision: Bullet - Sarue: HP =  %d\n", s->m_hp);

            m_associated.RequestDelete();
        }
        return;
    }
    
    Pigeon* pigeon = Pigeon::pigeon;
    if(!pigeon) return;
    if(!m_targetsPlayer)
    {
        if(IsColliding(m_collider->m_box, pigeon->m_collider->m_box, 0.0f, 0.0f))
        {
            pigeon->m_hp = pigeon->m_hp - 100;
            printf("Collision: Bullet - Pigeon : HP =  %d\n", pigeon->m_hp);

            m_associated.RequestDelete();
        }
        return;
    }
}

void Bullet::Start(){}

void Bullet::Update(float dt)
{
    m_associated.m_pos += m_speed_vec * dt;
    m_distanceLeft -= m_speed * dt; 
    if(m_distanceLeft <= 0.0f)
    {
        m_associated.RequestDelete();
        return;
    }

    CheckHitboxCollision();


}

void Bullet::Render(){}

bool Bullet::Is(std::string type)
{
    return (type == "Bullet");
}

int Bullet::GetDamage()
{
    return m_damage;
}

void Bullet::NotifyCollision(GameObject& other)
{
    // Bullet* b = (Bullet*) other.GetComponent("Bullet");
    // if(b != nullptr)
    // {
    //     return;
    // }

    // Player* p = (Player*) other.GetComponent("Player");
    // if(p != nullptr && !m_targetsPlayer)
    // {
    //     return; 
    // }

    // m_associated.RequestDelete();
}


