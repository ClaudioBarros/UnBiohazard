#pragma once

#include "Vec2.h"
#include "Component.h"
#include "Sprite2.h"
#include "Hitbox.h"
#include "Wall.h"

#define PLAYER_SPEED 250

#define SPEED_HISTORY_COUNT 64 

struct Player : Component
{
    static Player* player;

    Vec2 m_speedVec;
    bool m_flip;

    Vec2 m_speedHistory[SPEED_HISTORY_COUNT];
    int m_speedHistoryIndex = 0;
    
    Sprite2* m_sptIdleUp;
    Sprite2* m_sptIdleDown;
    Sprite2* m_sptIdleLeft;
    Sprite2* m_sptIdleRight;

    Sprite2* m_sptWalkUp;
    Sprite2* m_sptWalkDown;
    Sprite2* m_sptWalkLeft;
    Sprite2* m_sptWalkRight;

    Sprite2* m_sptRunUp;
    Sprite2* m_sptRunDown;
    Sprite2* m_sptRunLeft;
    Sprite2* m_sptRunRight;

    Sprite2* m_sptHitUp;
    Sprite2* m_sptHitDown;
    Sprite2* m_sptHitLeft;
    Sprite2* m_sptHitRight;

    Sprite2* m_sptDeathUp;
    Sprite2* m_sptDeathDown;
    Sprite2* m_sptDeathLeft;
    Sprite2* m_sptDeathRight;

    Sprite2* m_sptAttackUp;
    Sprite2* m_sptAttackDown;
    Sprite2* m_sptAttackLeft;
    Sprite2* m_sptAttackRight;

    Collider* m_collider;
    Hitbox* m_hitbox;

    enum Direction {UP, DOWN, LEFT, RIGHT};
    Direction m_renderDirection;

    Direction m_direction[2]; 

    Player(GameObject& associated);
    Player();
    void Start();
    void Update(float dt);
    void Render();
    bool Is(std::string);
    void NotifyCollision(GameObject& other);

private:
    void TurnOffSpriteRendering();

};
