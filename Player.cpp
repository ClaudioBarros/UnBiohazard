#include "Player.h"
#include "Game.h"
#include "Helper.h"
#include "Sprite2.h"
#include "InputManager.h"
#include "Camera.h"
#include "Collider.h"


Player::Player(GameObject& associated) : Component(associated)
{
    float scaleX = 3.0f;
    float scaleY = 3.0f;

    // Idle Sprites
    float idleFrameTime = 0.2;
    int numIdleFrames = 4;

    m_sptIdleUp = new Sprite2(associated, getAbsPath("/assets/img/player/idle_up.png"), numIdleFrames, idleFrameTime, true);
    m_sptIdleUp->SetScale(scaleX, scaleY);

    m_sptIdleDown = new Sprite2(associated, getAbsPath("/assets/img/player/idle_down.png"), numIdleFrames, idleFrameTime, true);
    m_sptIdleDown->SetScale(scaleX, scaleY);

    m_sptIdleLeft = new Sprite2(associated, getAbsPath("/assets/img/player/idle_left.png"), numIdleFrames, idleFrameTime, true);
    m_sptIdleLeft->SetScale(scaleX, scaleY);

    m_sptIdleRight = new Sprite2(associated, getAbsPath("/assets/img/player/idle_right.png"), numIdleFrames, idleFrameTime, true);
    m_sptIdleRight->SetScale(scaleX, scaleY);

    m_associated.AddComponent(m_sptIdleUp);
    m_associated.AddComponent(m_sptIdleDown);
    m_associated.AddComponent(m_sptIdleLeft);
    m_associated.AddComponent(m_sptIdleRight);

    // Walk Sprites
    float walkFrameTime = 0.2;
    int numWalkFrames = 4;

    m_sptWalkUp = new Sprite2(associated, getAbsPath("/assets/img/player/walk_up.png"), numWalkFrames, walkFrameTime, false);
    m_sptWalkUp->SetScale(scaleX, scaleY);

    m_sptWalkDown = new Sprite2(associated, getAbsPath("/assets/img/player/walk_down.png"), numWalkFrames, walkFrameTime, false);
    m_sptWalkDown->SetScale(scaleX, scaleY);

    m_sptWalkLeft = new Sprite2(associated, getAbsPath("/assets/img/player/walk_left.png"), numWalkFrames, walkFrameTime, false);
    m_sptWalkLeft->SetScale(scaleX, scaleY);

    m_sptWalkRight = new Sprite2(associated, getAbsPath("/assets/img/player/walk_right.png"), numWalkFrames, walkFrameTime, false);
    m_sptWalkRight->SetScale(scaleX, scaleY);

    m_associated.AddComponent(m_sptWalkUp);
    m_associated.AddComponent(m_sptWalkDown);
    m_associated.AddComponent(m_sptWalkLeft);
    m_associated.AddComponent(m_sptWalkRight);

    // Run Sprites
    float runFrameTime = 0.1;
    int numRunFrames = 4;

    m_sptRunUp = new Sprite2(associated, getAbsPath("/assets/img/player/run_up.png"), numRunFrames, runFrameTime, false);
    m_sptRunUp->SetScale(scaleX, scaleY);

    m_sptRunDown = new Sprite2(associated, getAbsPath("/assets/img/player/run_down.png"), numRunFrames, runFrameTime, false);
    m_sptRunDown->SetScale(scaleX, scaleY);

    m_sptRunLeft = new Sprite2(associated, getAbsPath("/assets/img/player/run_left.png"), numRunFrames, runFrameTime, false);
    m_sptRunLeft->SetScale(scaleX, scaleY);

    m_sptRunRight = new Sprite2(associated, getAbsPath("/assets/img/player/run_right.png"), numRunFrames, runFrameTime, false);
    m_sptRunRight->SetScale(scaleX, scaleY);

    m_associated.AddComponent(m_sptRunUp);
    m_associated.AddComponent(m_sptRunDown);
    m_associated.AddComponent(m_sptRunLeft);
    m_associated.AddComponent(m_sptRunRight);

    // Hit Sprites
    float hitFrameTime = 0.2;
    int numHitFrames = 2;

    m_sptHitUp = new Sprite2(associated, getAbsPath("/assets/img/player/hit_up.png"), numHitFrames, hitFrameTime, false);
    m_sptHitUp->SetScale(scaleX, scaleY);

    m_sptHitDown = new Sprite2(associated, getAbsPath("/assets/img/player/hit_down.png"), numHitFrames, hitFrameTime, false);
    m_sptHitDown->SetScale(scaleX, scaleY);

    m_sptHitLeft = new Sprite2(associated, getAbsPath("/assets/img/player/hit_left.png"), numHitFrames, hitFrameTime, false);
    m_sptHitLeft->SetScale(scaleX, scaleY);

    m_sptHitRight = new Sprite2(associated, getAbsPath("/assets/img/player/hit_right.png"), numHitFrames, hitFrameTime, false);
    m_sptHitRight->SetScale(scaleX, scaleY);

    m_associated.AddComponent(m_sptHitUp);
    m_associated.AddComponent(m_sptHitDown);
    m_associated.AddComponent(m_sptHitLeft);
    m_associated.AddComponent(m_sptHitRight);

    // Death Sprites
    float deathFrameTime = 0.2;
    int numDeathFrames = 3;

    m_sptDeathUp = new Sprite2(associated, getAbsPath("/assets/img/player/death_up.png"), numDeathFrames, deathFrameTime, false);
    m_sptDeathUp->SetScale(scaleX, scaleY);

    m_sptDeathDown = new Sprite2(associated, getAbsPath("/assets/img/player/death_down.png"), numDeathFrames, deathFrameTime, false);
    m_sptDeathDown->SetScale(scaleX, scaleY);

    m_sptDeathLeft = new Sprite2(associated, getAbsPath("/assets/img/player/death_left.png"), numDeathFrames, deathFrameTime, false);
    m_sptDeathLeft->SetScale(scaleX, scaleY);

    m_sptDeathRight = new Sprite2(associated, getAbsPath("/assets/img/player/death_right.png"), numDeathFrames, deathFrameTime, false);
    m_sptDeathRight->SetScale(scaleX, scaleY);

    m_associated.AddComponent(m_sptDeathUp);
    m_associated.AddComponent(m_sptDeathDown);
    m_associated.AddComponent(m_sptDeathLeft);
    m_associated.AddComponent(m_sptDeathRight);

    // Attack Sprites
    float attackFrameTime = 0.2;
    int numAttackFrames = 4;

    m_sptAttackUp = new Sprite2(associated, getAbsPath("/assets/img/player/attack_up.png"), numAttackFrames, attackFrameTime, false);
    m_sptAttackUp->SetScale(scaleX, scaleY);

    m_sptAttackDown = new Sprite2(associated, getAbsPath("/assets/img/player/attack_down.png"), numAttackFrames, attackFrameTime, false);
    m_sptAttackDown->SetScale(scaleX, scaleY);

    m_sptAttackLeft = new Sprite2(associated, getAbsPath("/assets/img/player/attack_left.png"), numAttackFrames, attackFrameTime, false);
    m_sptAttackLeft->SetScale(scaleX, scaleY);

    m_sptAttackRight = new Sprite2(associated, getAbsPath("/assets/img/player/attack_right.png"), numAttackFrames, attackFrameTime, false);
    m_sptAttackRight->SetScale(scaleX, scaleY);

    m_associated.AddComponent(m_sptAttackUp);
    m_associated.AddComponent(m_sptAttackDown);
    m_associated.AddComponent(m_sptAttackLeft);
    m_associated.AddComponent(m_sptAttackRight);

    //Collider
    Collider* collider = new Collider(associated);
    m_associated.AddComponent(collider);

    //members
    m_direction = DOWN;
    m_speedVec = Vec2(0.0f, 0.0f);
    m_flip = false;
}

void Player::Start(){}

void Player::TurnOffSpriteRendering()
{
    m_sptIdleUp->m_isRendering = false;
    m_sptIdleDown->m_isRendering = false;
    m_sptIdleLeft->m_isRendering = false;
    m_sptIdleRight->m_isRendering = false;

    m_sptWalkUp->m_isRendering = false;
    m_sptWalkDown->m_isRendering = false;
    m_sptWalkLeft->m_isRendering = false;
    m_sptWalkRight->m_isRendering = false;

    m_sptRunUp->m_isRendering = false;
    m_sptRunDown->m_isRendering = false;
    m_sptRunLeft->m_isRendering = false;
    m_sptRunRight->m_isRendering = false;

    m_sptHitUp->m_isRendering = false;
    m_sptHitDown->m_isRendering = false;
    m_sptHitLeft->m_isRendering = false;
    m_sptHitRight->m_isRendering = false;

    m_sptDeathUp->m_isRendering = false;
    m_sptDeathDown->m_isRendering = false;
    m_sptDeathLeft->m_isRendering = false;
    m_sptDeathRight->m_isRendering = false;

    m_sptAttackUp->m_isRendering = false;
    m_sptAttackDown->m_isRendering = false;
    m_sptAttackLeft->m_isRendering = false;
    m_sptAttackRight->m_isRendering = false;
}


void Player::Update(float dt)
{
    TurnOffSpriteRendering();

    switch(m_direction)
    {
        case UP:
        {
            m_sptIdleUp->m_isRendering = true;            
        } break;
        case DOWN:
        {
            m_sptIdleDown->m_isRendering = true;            
        } break;
        case LEFT:
        {
            m_sptIdleLeft->m_isRendering = true;            
        } break;
        case RIGHT:
        {
            m_sptIdleRight->m_isRendering = true;            
        } break;
    }

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

    //Move Up-Right
    if(InputManager::GetInstance().IsKeyDown(KEY_W) &&
       InputManager::GetInstance().IsKeyDown(KEY_D))
    {
        TurnOffSpriteRendering();
        skipVerticalMovement = true; 
        skipHorizontalMovement = true; 
        m_sptWalkRight->m_isRendering = true;
        m_speedVec = speed * normalize(Vec2(1.0f, -1.0f));
        m_direction = RIGHT;
    }

    //Move Up-Left
    if(InputManager::GetInstance().IsKeyDown(KEY_W) &&
       InputManager::GetInstance().IsKeyDown(KEY_A))
    {
        TurnOffSpriteRendering();
        skipVerticalMovement = true; 
        skipHorizontalMovement = true; 
        m_sptWalkLeft->m_isRendering = true;
        m_speedVec = speed * normalize(Vec2(-1.0f, -1.0f));
        m_direction = LEFT;
    }

    //Move Down-Right
    if(InputManager::GetInstance().IsKeyDown(KEY_S) &&
       InputManager::GetInstance().IsKeyDown(KEY_D))
    {
        TurnOffSpriteRendering();
        skipVerticalMovement = true; 
        skipHorizontalMovement = true; 
        m_sptWalkRight->m_isRendering = true;
        m_speedVec = speed * normalize(Vec2(1.0f, 1.0f));
        m_direction = RIGHT;
    }

    //Move Down-Left
    if(InputManager::GetInstance().IsKeyDown(KEY_S) &&
       InputManager::GetInstance().IsKeyDown(KEY_A))
    {
        TurnOffSpriteRendering();
        skipVerticalMovement = true; 
        skipHorizontalMovement = true; 
        m_sptWalkLeft->m_isRendering = true;
        m_speedVec = speed * normalize(Vec2(-1.0f, 1.0f));
        m_direction = LEFT;
    }

    //Move Up
    if(InputManager::GetInstance().IsKeyDown(KEY_W) && 
       !skipVerticalMovement)
    {
        TurnOffSpriteRendering();
        m_sptWalkUp->m_isRendering = true;
        m_speedVec = Vec2(0.0f, -speed);
        m_direction = UP;
    }
    
    //Move Down
    if(InputManager::GetInstance().IsKeyDown(KEY_S) &&
       !skipVerticalMovement)
    {
        TurnOffSpriteRendering();
        m_sptWalkDown->m_isRendering = true;
        m_speedVec = Vec2(0.0f, speed);
        m_direction = DOWN;
    }

    //Move Left
    if(InputManager::GetInstance().IsKeyDown(KEY_A) &&
       !skipHorizontalMovement)
    {
        TurnOffSpriteRendering();
        m_sptWalkLeft->m_isRendering = true;
        m_speedVec = Vec2(-speed, 0.0f);
        m_direction = LEFT;
    }

    //Move Right
    if(InputManager::GetInstance().IsKeyDown(KEY_D) &&
       !skipHorizontalMovement)
    {
        TurnOffSpriteRendering();
        m_sptWalkRight->m_isRendering = true;
        m_speedVec = Vec2(speed, 0.0f);
        m_direction = RIGHT;
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

