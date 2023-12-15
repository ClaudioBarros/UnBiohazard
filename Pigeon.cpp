#include "Pigeon.h"
#include "Player.h"
#include "Sprite2.h"
#include "Camera.h"
#include "InputManager.h"
#include "Game.h"
#include "Collider.h"
#include "Sound.h"
#include "Helper.h"

#define PIGEON_SPEED 250.0f

Pigeon::Pigeon(GameObject& associated, float restTime) : Component(associated)
{
    float idleFrameTime = 0.2;
    int numIdleFrames = 5;
    m_sptIdleLeft = new Sprite2(associated, 
                    getAbsPath("/assets/img/pombo_parado_esq.png"),
                    numIdleFrames,
                    idleFrameTime,
                    true);
    m_sptIdleRight = new Sprite2(associated, 
                    getAbsPath("/assets/img/pombo_parado_dir.png"),
                    numIdleFrames,
                    idleFrameTime,
                    true);
    m_sptMovingLeft = new Sprite2(associated, 
                      getAbsPath("/assets/img/pombo_voando_esq.png"),
                      1,
                      1,
                      true);
    m_sptMovingRight = new Sprite2(associated, 
                      getAbsPath("/assets/img/pombo_voando_dir.png"),
                      1,
                      1,
                      true);

    m_sptIdleLeft->SetScale(3.0f, 3.0f);
    m_sptIdleRight->SetScale(3.0f, 3.0f);
    m_sptMovingLeft->SetScale(3.0f, 3.0f);
    m_sptMovingRight->SetScale(3.0f, 3.0f);

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
}

Pigeon::~Pigeon(){}

void Pigeon::Start(){}

void Pigeon::SetDirection()
{
    if(Player::player->m_associated.m_pos.x() > m_associated.m_pos.x())
        m_direction = RIGHT;
    else
        m_direction = LEFT;
}

void Pigeon::CheckPlayerHitboxCollision()
{
    Player* p = Player::player;
    if(IsColliding(m_collider->m_box, Player::player->m_hitbox->m_collider->m_box, 0.0f, 0.0f))
    {
        printf("Collision: Pigeon - Player \n");

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

void Pigeon::Update(float dt)
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
                m_speedVec = PIGEON_SPEED * normalize(m_destination - m_associated.m_pos);
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

            m_state = RESTING;
        }
    }

    CheckPlayerHitboxCollision();
}


void Pigeon::Render()
{
         
}

bool Pigeon::Is(std::string type)
{
    return (type == "Pigeon");
}

void Pigeon::NotifyCollision(GameObject& other)
{
    // Player* p = (Player*) other.GetComponent("Player");
    // if(p != nullptr)
    // {
    //     printf("Collision: Pigeon - Player \n");

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

