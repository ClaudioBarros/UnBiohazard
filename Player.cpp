#include "Player.h"
#include "Game.h"
#include "Helper.h"
#include "Sprite2.h"
#include "InputManager.h"
#include "Camera.h"
#include "Collider.h"
#include "Wall.h"
#include "Bullet.h"

Player* Player::player = nullptr;

Player::Player(GameObject& associated) : Component(associated)
{
    float scaleX = 2.0f;
    float scaleY = 2.0f;

    // Attack Sprites
    float attackFrameTime = 0.15;
    int numAttackFrames = 5;

    m_sptAttackUp = new Sprite2(associated, getAbsPath("/assets/img/player/main/attack_up.png"), numAttackFrames, attackFrameTime, false);
    m_sptAttackUp->SetScale(scaleX, scaleY);

    m_sptAttackDown = new Sprite2(associated, getAbsPath("/assets/img/player/main/attack_down.png"), numAttackFrames, attackFrameTime, false);
    m_sptAttackDown->SetScale(scaleX, scaleY);

    m_sptAttackLeft = new Sprite2(associated, getAbsPath("/assets/img/player/main/attack_left.png"), numAttackFrames, attackFrameTime, false);
    m_sptAttackLeft->SetScale(scaleX, scaleY);

    m_sptAttackRight = new Sprite2(associated, getAbsPath("/assets/img/player/main/attack_right.png"), numAttackFrames, attackFrameTime, false);
    m_sptAttackRight->SetScale(scaleX, scaleY);

    m_associated.AddComponent(m_sptAttackUp);
    m_associated.AddComponent(m_sptAttackDown);
    m_associated.AddComponent(m_sptAttackLeft);
    m_associated.AddComponent(m_sptAttackRight);

    // Idle Sprites
    float idleFrameTime = 0.1;
    int numIdleFrames = 6;

    m_sptIdleUp = new Sprite2(associated, getAbsPath("/assets/img/player/main/idle_up.png"), numIdleFrames, idleFrameTime, true);
    m_sptIdleUp->SetScale(scaleX, scaleY);

    m_sptIdleDown = new Sprite2(associated, getAbsPath("/assets/img/player/main/idle_down.png"), numIdleFrames, idleFrameTime, true);
    m_sptIdleDown->SetScale(scaleX, scaleY);

    m_sptIdleLeft = new Sprite2(associated, getAbsPath("/assets/img/player/main/idle_left.png"), numIdleFrames, idleFrameTime, true);
    m_sptIdleLeft->SetScale(scaleX, scaleY);

    m_sptIdleRight = new Sprite2(associated, getAbsPath("/assets/img/player/main/idle_right.png"), numIdleFrames, idleFrameTime, true);
    m_sptIdleRight->SetScale(scaleX, scaleY);

    m_associated.AddComponent(m_sptIdleUp);
    m_associated.AddComponent(m_sptIdleDown);
    m_associated.AddComponent(m_sptIdleLeft);
    m_associated.AddComponent(m_sptIdleRight);

    // Walk Sprites
    float walkFrameTime = 0.1;
    int numWalkFrames = 6;

    m_sptWalkUp = new Sprite2(associated, getAbsPath("/assets/img/player/main/walk_up.png"), numWalkFrames, walkFrameTime, false);
    m_sptWalkUp->SetScale(scaleX, scaleY);

    m_sptWalkDown = new Sprite2(associated, getAbsPath("/assets/img/player/main/walk_down.png"), numWalkFrames, walkFrameTime, false);
    m_sptWalkDown->SetScale(scaleX, scaleY);

    m_sptWalkLeft = new Sprite2(associated, getAbsPath("/assets/img/player/main/walk_left.png"), numWalkFrames, walkFrameTime, false);
    m_sptWalkLeft->SetScale(scaleX, scaleY);

    m_sptWalkRight = new Sprite2(associated, getAbsPath("/assets/img/player/main/walk_right.png"), numWalkFrames, walkFrameTime, false);
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


    //Collider
    m_collider = new Collider(associated);
    m_associated.AddComponent(m_collider);
    m_collider->SetScale(Vec2(0.6f, 0.8f));
    m_collider->SetOffset(Vec2(20.0f, 60.0f));
    // collider->SetOffset(Vec2(0.3f * m_associated.m_box.z(), 
    //                          0.7f * m_associated.m_box.w()));
    
    //Hitbox
    m_hitbox = new Hitbox(associated, 
                          m_associated.m_pos,
                          Vec2(m_associated.m_box.z(), m_associated.m_box.w()),
                          Vec2(0.8f, 1.8f),
                          Vec2(12.0f, 0.0f));
                         

    //members
    m_renderDirection = DOWN;
    m_speedVec = Vec2(0.0f, 0.0f);
    m_flip = false;
    for(int i = 0; i < SPEED_HISTORY_COUNT; i++)
    {
        m_speedHistory[i] = Vec2(0.0f, 0.0f);
    }
    m_attackTimeSeconds = attackFrameTime * numAttackFrames;
    m_attackTimer.time = 0;
    m_isAttacking = false;

    m_hp = 1000;

    player = this;
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

void Player::Shoot(Vec2 target)
{
    Vec2 pos = getRectCenter(m_associated.m_box); 

    GameObject* obj = new GameObject();
    obj->m_pos = pos;
    Vec2 dir = target - pos;
    float angle = atan2(dir.y(), dir.x());
    obj->m_angleDeg = RAD2DEG(angle);

    float bulletSpeed = 300.0f;
    float bulletDamage = 100; 
    float bulletMaxDist = 100.0f;
    float bulletFrameCount = 3;
    float bulletFrameTime = 0.3;
    bool  targetsPlayer = false;
    Bullet* bullet = new Bullet(
        *obj, 
        targetsPlayer,
        angle,
        bulletSpeed,
        bulletDamage,
        bulletMaxDist,
        bulletFrameCount,
        bulletFrameTime,
        getAbsPath("/assets/img/minionbullet2.png")
    );

    obj->AddComponent(bullet);

    Game::GetInstance().GetState().AddObject(obj);
}

void Player::Attack()
{
    switch(m_renderDirection)
    {
        case UP:
        {
            m_sptAttackUp->m_isRendering = true;            
        } break;
        case DOWN:
        {
            m_sptAttackDown->m_isRendering = true;            
        } break;
        case LEFT:
        {
            m_sptAttackLeft->m_isRendering = true;            
        } break;
        case RIGHT:
        {
            m_sptAttackRight->m_isRendering = true;            
        } break;
    }
    
}

void Player::Update(float dt)
{
    TurnOffSpriteRendering();

    switch(m_renderDirection)
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
        m_renderDirection = RIGHT;
        m_direction[0] = RIGHT;
        m_direction[1] = UP;
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
        m_renderDirection = LEFT;
        m_direction[0] = LEFT;
        m_direction[1] = UP;
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
        m_renderDirection = RIGHT;
        m_direction[0] = RIGHT;
        m_direction[1] = DOWN;
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
        m_renderDirection = LEFT;
        m_direction[0] = LEFT;
        m_direction[1] = DOWN;
    }

    //Move Up
    if(InputManager::GetInstance().IsKeyDown(KEY_W) && 
       !skipVerticalMovement)
    {
        TurnOffSpriteRendering();
        m_sptWalkUp->m_isRendering = true;
        m_speedVec = Vec2(0.0f, -speed);
        m_renderDirection = UP;
        m_direction[1] = UP;
    }
    
    //Move Down
    if(InputManager::GetInstance().IsKeyDown(KEY_S) &&
       !skipVerticalMovement)
    {
        TurnOffSpriteRendering();
        m_sptWalkDown->m_isRendering = true;
        m_speedVec = Vec2(0.0f, speed);
        m_renderDirection = DOWN;
        m_direction[1] = DOWN;
    }

    //Move Left
    if(InputManager::GetInstance().IsKeyDown(KEY_A) &&
       !skipHorizontalMovement)
    {
        TurnOffSpriteRendering();
        m_sptWalkLeft->m_isRendering = true;
        m_speedVec = Vec2(-speed, 0.0f);
        m_renderDirection = LEFT;
        m_direction[0] = LEFT;
    }

    //Move Right
    if(InputManager::GetInstance().IsKeyDown(KEY_D) &&
       !skipHorizontalMovement)
    {
        TurnOffSpriteRendering();
        m_sptWalkRight->m_isRendering = true;
        m_speedVec = Vec2(speed, 0.0f);
        m_renderDirection = RIGHT;
        m_direction[0] = RIGHT;
    }

    if(InputManager::GetInstance().MousePress(LEFT_MOUSE_BUTTON))
    {
        if(!m_isAttacking) //if previous attack is not still happening
        {
            m_isAttacking = true;
            m_attackTimer.Restart();
            float mouseX = (float) InputManager::GetInstance().GetMouseX();
            float mouseY = (float) InputManager::GetInstance().GetMouseY();
            Vec2 mouseVec = Camera::m_pos + Vec2(mouseX, mouseY);
            Shoot(mouseVec);
        }
    }

    if(m_isAttacking)
    {
        m_attackTimer.Update(dt);
        if(m_attackTimer.time >= m_attackTimeSeconds)
        {
            m_isAttacking = false;
        }
        else
        {
            TurnOffSpriteRendering();
            Attack();
        }
    }
    if(m_attackTimeSeconds)

    m_speedHistory[m_speedHistoryIndex % SPEED_HISTORY_COUNT] = m_speedVec;
    m_speedHistoryIndex = (m_speedHistoryIndex+1) % SPEED_HISTORY_COUNT;
    m_associated.m_pos += m_speedVec;
}


void Player::Render()
{
}

bool Player::Is(std::string type)
{
    return (type == "Player");
}

void solveWallCollision(GameObject *associated, Collider* playerCollider, Collider* wall, Vec2 speed)
{

    Player* player = (Player*)associated->GetComponent("Player");
    Rect& pBox = playerCollider->m_box;
    Rect& wBox = wall->m_box;

    float pWidth = pBox.z();
    float pHeight = pBox.w();

    float wallWidth = wBox.z();
    float wallHeight = wBox.w();

    float pLeftX = pBox.x();
    float pRightX = pLeftX + pWidth;
    float pTopY = pBox.y();
    float pBottomY = pTopY + pHeight;

    float wallLeftX = wBox.x();
    float wallRightX = wallLeftX + wallWidth;
    float wallTopY = wBox.y();
    float wallBottomY = wallTopY + wallHeight;

    //get overlap
    Vec2 overlap(0.0f, 0.0f);
    if(pLeftX < wallLeftX)
    {
        if(pRightX < wallRightX)
        {
            overlap.setX(pRightX - wallLeftX);
        }
        else
        {
            overlap.setX(wallWidth);
        }
    }
    else //pLeftX >= wallLeftX
    {
        if(pRightX > wallRightX)
        {
            overlap.setX(wallRightX - pLeftX);
        }
        else
        {
            overlap.setX(pWidth);
        }
    }

    if(pTopY < wallTopY)
    {
        if(pBottomY < wallBottomY)
        {
            overlap.setY(pBottomY - wallTopY);
        }
        else
        {
            overlap.setY(wallHeight);
        }
    }
    else //pTopY > wallTopY
    {
        if(pBottomY > wallBottomY)
        {
            overlap.setY(wallBottomY - pTopY);
        }
        else
        {
            overlap.setY(pHeight);
        }
    }

    //solve collision:

    printf("-------- Wall Collision ----------: \n");
    printf("\tplayerBoxCoords = (%f , %f, %f , %f)\n", pLeftX, pRightX, pTopY, pBottomY);
    printf("\twallBoxCoords = (%f , %f, %f , %f)\n", wallLeftX, wallRightX, wallTopY, wallBottomY);

    printf("\toverlap = (%f ; %f)\n", overlap.x(), overlap.y());
    printf("\tspeed = (%f ; %f)\n", speed.x(), speed.y());
    if(overlap.x() > overlap.y())
    {
        if(player->m_direction[1] == Player::Direction::DOWN)
        {
            //player is moving down
            float oldY = pBox.y();
            float newY = wallTopY - pHeight - 1.0f; 
            pBox.setY(newY);

            float displacement = fabs(oldY - newY);
            printf("\t(oldY, newY) : (%f ; %f)\n", oldY, newY);
            printf("\t oldPos = (%f, %f)\n", associated->m_pos.x(), associated->m_pos.y());
            associated->m_pos -= Vec2(0.0f, displacement); 
            printf("\t newPos = (%f, %f)\n", associated->m_pos.x(), associated->m_pos.y());
        }
        else
        {
            //player is moving up
            float oldY = pBox.y();
            float newY = wallBottomY + 1.0f; 
            pBox.setY(newY);

            float displacement = fabs(oldY - newY);
            printf("\t(oldY, newY) : (%f ; %f)\n", oldY, newY);
            printf("\t oldPos = (%f, %f)\n", associated->m_pos.x(), associated->m_pos.y());
            associated->m_pos += Vec2(0.0f, displacement); 
            printf("\tnewPos = (%f, %f)\n", associated->m_pos.x(), associated->m_pos.y());
                
        }
    }
    else
    {
        // if(speed.x() > 0)
        if(player->m_direction[0] == Player::Direction::RIGHT)
        {
            //player is moving right
            float oldX = pBox.x();
            float newX = wallLeftX - pWidth - 1.0f; 
            pBox.setX(newX);

            float displacement = fabs(oldX - newX);
            printf("\t(oldX, newX) : (%f ; %f)\n", oldX, newX);
            printf("\t oldPos = (%f, %f)\n", associated->m_pos.x(), associated->m_pos.y());
            associated->m_pos -= Vec2(displacement, 0); 
            printf("\t newPos = (%f, %f)\n", associated->m_pos.x(), associated->m_pos.y());
        }
        else
        {
            //player is moving left
            float oldX = pBox.x();
            float newX = wallRightX + 1.0f; 
            pBox.setX(newX);

            float displacement = fabs(oldX - newX);
            printf("\t(oldX, newX) : (%f ; %f)\n", oldX, newX);
            printf("\t oldPos = (%f, %f)\n", associated->m_pos.x(), associated->m_pos.y());
            associated->m_pos += Vec2(displacement, 0); 
            printf("\t newPos = (%f, %f)\n", associated->m_pos.x(), associated->m_pos.y());
        }
    }

    printf("-------------------------------");
}

void Player::NotifyCollision(GameObject& other)
{
    Wall* w = (Wall*) other.GetComponent("Wall");

    if(w != nullptr)
    {
        printf("Collision: Player - Wall\n");
        Collider* playerCollider = (Collider*) m_associated.GetComponent("Collider");
        Collider* wallCollider = (Collider*) other.GetComponent("Collider");  
        
        solveWallCollision(&m_associated, playerCollider, wallCollider, m_speedVec);
    }

}

