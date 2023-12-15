#include "Sarue.h"
#include "Player.h"
#include "Sprite2.h"
#include "Camera.h"
#include "InputManager.h"
#include "Game.h"
#include "Collider.h"
#include "Sound.h"
#include "Helper.h"
#include "Bullet.h"

#define SARUE_SPEED 400.0f

Sarue* Sarue::sarue = nullptr;

Sarue::Sarue(GameObject& associated, float restTime) : Component(associated)
{
    float frameTime = 0.2;
    int numFrames = 6;
    m_sptIdleLeft = new Sprite2(associated, 
                    getAbsPath("/assets/img/rato_esquerda.png"),
                    numFrames,
                    frameTime,
                    true);
    m_sptIdleRight = new Sprite2(associated, 
                    getAbsPath("/assets/img/rato_direita.png"),
                    numFrames,
                    frameTime,
                    true);
    m_sptMovingLeft = new Sprite2(associated, 
                      getAbsPath("/assets/img/rato_esquerda.png"),
                      numFrames,
                      frameTime,
                      true);
    m_sptMovingRight = new Sprite2(associated, 
                      getAbsPath("/assets/img/rato_direita.png"),
                      numFrames,
                      frameTime,
                      true);

    m_sptIdleLeft->SetScale(2.0f, 2.0f);
    m_sptIdleRight->SetScale(2.0f, 2.0f);
    m_sptMovingLeft->SetScale(2.0f, 2.0f);
    m_sptMovingRight->SetScale(2.0f, 2.0f);

    m_associated.AddComponent(m_sptIdleLeft);
    m_associated.AddComponent(m_sptIdleRight);
    m_associated.AddComponent(m_sptMovingLeft);
    m_associated.AddComponent(m_sptMovingRight);

    m_collider = new Collider(associated);
    m_associated.AddComponent(m_collider);

    m_speedVec = Vec2(0.0, 0.0);
    m_hp = 1000;
    m_state = RESTING; 
    m_restTime = restTime;

    sarue = this;
}

Sarue::~Sarue()
{
    sarue = nullptr;
}

void Sarue::Start(){}

void Sarue::SetDirection()
{
    if(Player::player->m_associated.m_pos.x() > m_associated.m_pos.x())
        m_direction = RIGHT;
    else
        m_direction = LEFT;
}

void Sarue::CheckPlayerHitboxCollision()
{
    Player* p = Player::player;
    if(IsColliding(m_collider->m_box, Player::player->m_hitbox->m_collider->m_box, 0.0f, 0.0f))
    {
        printf("Collision: Sarue - Player \n");

        Helper::Direction dirX;
        Helper::Direction dirY;
    
        if(m_associated.m_pos.y() > p->m_associated.m_pos.y())
            dirY = Helper::Direction::DOWN;
        else
            dirY = Helper::Direction::UP;

        if(m_direction == LEFT)
            dirX = Helper::Direction::LEFT; 
        else
            dirX = Helper::Direction::RIGHT;

        Collider::solveWallCollision(dirX, dirY, 
                                     &m_associated, 
                                     m_collider,
                                     p->m_hitbox->m_collider,
                                     m_speedVec);
        m_restTimer.Restart();
        m_state = RESTING;
    }
}

void Sarue::Shoot(Vec2 target)
{
    Vec2 pos = getRectCenter(m_associated.m_box); 

    GameObject* obj = new GameObject();
    obj->m_pos = pos;
    Vec2 dir = target - pos;
    float angle = atan2(dir.y(), dir.x());
    obj->m_angleDeg = RAD2DEG(angle);

    float bulletSpeed = 300.0f;
    float bulletDamage = 50; 
    float bulletMaxDist = 1500.0f;
    float bulletFrameCount = 3;
    float bulletFrameTime = 0.3;
    bool  targetsPlayer = true;
    Bullet* bullet = new Bullet(
        *obj, 
        targetsPlayer,
        angle,
        bulletSpeed,
        bulletDamage,
        bulletMaxDist,
        bulletFrameCount,
        bulletFrameTime,
        getAbsPath("/assets/img/bullet.png")
    );

    obj->AddComponent(bullet);

    Game::GetInstance().GetState().AddObject(obj);
}

void Sarue::Update(float dt)
{
    SetDirection();

    if(m_hp <= 0)
    {
        m_associated.RequestDelete();
        return;
    }

    if(m_state == RESTING)
    {
        if(m_direction == LEFT)
        {
            m_sptIdleLeft->m_isRendering = true;
            m_sptIdleRight->m_isRendering = false;
            m_sptMovingLeft->m_isRendering = false;
            m_sptMovingRight->m_isRendering = false;
        }
        else
        {
            m_sptIdleLeft->m_isRendering = false;
            m_sptIdleRight->m_isRendering = true;
            m_sptMovingLeft->m_isRendering = false;
            m_sptMovingRight->m_isRendering = false;
        }

        m_restTimer.Update(dt);
        if(m_restTimer.time >= m_restTime)
        { 
            if(Player::player != nullptr)
            {
                m_destination = Player::player->m_associated.m_pos;
                m_state = MOVING;

                //calculate speed vec
                m_speedVec = SARUE_SPEED * normalize(m_destination - m_associated.m_pos);
            }
            m_restTimer.Restart();
        }
    }

    if(m_state == MOVING)
    {
        if(m_direction == LEFT)
        {
            m_sptIdleLeft->m_isRendering = false;
            m_sptIdleRight->m_isRendering = false;
            m_sptMovingLeft->m_isRendering = true;
            m_sptMovingRight->m_isRendering = false;
        }
        else
        {
            m_sptIdleLeft->m_isRendering = false;
            m_sptIdleRight->m_isRendering = false;
            m_sptMovingLeft->m_isRendering = false;
            m_sptMovingRight->m_isRendering = true;
        }

        m_associated.m_pos += m_speedVec * dt;
        if(length(m_associated.m_pos - m_destination) < 10.0f)
        {
            m_associated.m_pos = m_destination;

            if(Player::player != nullptr)
            {
                Vec2 target = Player::player->m_associated.m_pos;
                Shoot(target);
            }

            m_state = RESTING;
        }
    }

    CheckPlayerHitboxCollision();
}


void Sarue::Render()
{
         
}

bool Sarue::Is(std::string type)
{
    return (type == "Sarue");
}

void Sarue::NotifyCollision(GameObject& other)
{
    // Player* p = (Player*) other.GetComponent("Player");
    // if(p != nullptr)
    // {
    //     printf("Collision: Sarue - Player \n");

    //     Helper::Direction dirX;
    //     Helper::Direction dirY;
    // 
    //     if(m_associated.m_pos.y() > p->m_associated.m_pos.y())
    //         dirY = Helper::Direction::DOWN;
    //     else
    //         dirY = Helper::Direction::UP;

    //     if(m_direction == LEFT)
    //         dirX = Helper::Direction::LEFT; 
    //     else
    //         dirX = Helper::Direction::RIGHT;

    //     Collider::solveWallCollision(dirX, dirY, 
    //                                  &m_associated, 
    //                                  m_collider,
    //                                  p->m_hitbox->m_collider,
    //                                  m_speedVec);
    // }
}


