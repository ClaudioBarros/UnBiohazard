#include "Player.h"
#include "Game.h"
#include "Helper.h"
#include "Sprite2.h"
#include "InputManager.h"
#include "Camera.h"
#include "Collider.h"

Player::Player(GameObject& associated) : Component(associated)
{
    int numIdleFrames = 10;
    float idleFrameTime = 0.2;
    Sprite2* idleSpt = new Sprite2(associated, getAbsPath("/assets/img/player_idle_48x48.png"), numIdleFrames, idleFrameTime, true);
    idleSpt->SetScale(3.0f, 3.0f);
    m_spriteIdle = idleSpt;

    int numWalkingFrames = 8;
    float walkingFrameTime = 0.2;
    Sprite2* walkingSpt = new Sprite2(associated, getAbsPath("/assets/img/player_walk_48x48.png"), numWalkingFrames, idleFrameTime, false);
    walkingSpt->SetScale(3.0f, 3.0f);
    m_spriteWalking = walkingSpt;

    Collider* collider = new Collider(associated);

    m_associated.AddComponent(idleSpt);
    m_associated.AddComponent(walkingSpt);
    m_associated.AddComponent(collider);

    m_speedVec = Vec2(0.0f, 0.0f);
    m_flip = false;

}

void Player::Start(){}

void Player::Update(float dt)
{
    m_spriteIdle->m_isRendering = true;
    m_flip ? m_spriteIdle->m_flipTexture = true : m_spriteIdle->m_flipTexture = false;
    m_spriteWalking->m_isRendering = false;

    float speed = PLAYER_SPEED * dt;
    m_speedVec = Vec2(0.0f, 0.0f);

    //check if keys are pressed at the same time
    bool skipVerticalMovement = false; 
    if(InputManager::GetInstance().IsKeyDown(KEY_W) &&
       InputManager::GetInstance().IsKeyDown(KEY_S))
    {
        skipVerticalMovement = true; 
    }

    bool skipHorizontalMovement = false; 
    if(InputManager::GetInstance().IsKeyDown(KEY_A) &&
       InputManager::GetInstance().IsKeyDown(KEY_D))
    {
        skipHorizontalMovement = true; 
    }

    //Move Up
    if(InputManager::GetInstance().IsKeyDown(KEY_W) && 
       !skipVerticalMovement)
    {
        m_spriteIdle->m_isRendering = false;
        m_spriteWalking->m_isRendering = true;

        m_speedVec += Vec2(0.0f, speed);
    }
    
    //Move Down
    if(InputManager::GetInstance().IsKeyDown(KEY_S) &&
       !skipVerticalMovement)
    {
        m_spriteIdle->m_isRendering = false;
        m_spriteWalking->m_isRendering = true;

        m_speedVec += Vec2(0.0f, speed);
    }

    //Move Left
    if(InputManager::GetInstance().IsKeyDown(KEY_A) &&
       !skipHorizontalMovement)
    {
        m_spriteIdle->m_isRendering = false;
        m_spriteWalking->m_isRendering = true;
        m_spriteWalking->m_flipTexture = true;
        m_flip = true;

        m_speedVec -= Vec2(speed, 0.0f);
    }

    //Move Right
    if(InputManager::GetInstance().IsKeyDown(KEY_D) &&
       !skipHorizontalMovement)
    {
        m_spriteIdle->m_isRendering = false;
        m_spriteWalking->m_isRendering = true;
        m_spriteWalking->m_flipTexture = false;
        m_flip = false;

        m_speedVec += Vec2(speed, 0.0f);
    }

    m_associated.m_pos += m_speedVec;
}

void Player::Render()
{
}

bool Player::Is(std::string type)
{
    return (type == "Player");
}

void Player::NotifyCollision(GameObject& other){}

