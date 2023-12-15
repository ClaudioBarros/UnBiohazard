#include "Collider.h"    
#include "Camera.h"
#include "Player.h"
#include "Game.h"
#include <SDL/SDL.h>
#include <SDL_image/SDL_image.h>

Collider::Collider(GameObject& associated, Vec2 scale, Vec2 offset)
: Component(associated)
{
    m_scale = scale;
    m_offset = offset;
    m_box = Rect();
}
    
void Collider::Start()
{
}

void Collider::Update(float dt)
{
    m_box = m_associated.m_box * Rect(1.0f, 1.0f, m_scale.x(), m_scale.y());
    m_box.setX(m_box.x() + m_offset.x());
    m_box.setY(m_box.y() + m_offset.y());
}

void Collider::Render()
{
    SDL_Rect dstRect;
    dstRect.x = (int) m_box.x() - Camera::m_pos.x(); 
    dstRect.y = (int) m_box.y() - Camera::m_pos.y();
    dstRect.w = (int) m_box.z(); 
    dstRect.h = (int) m_box.w();;

 //    SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 255, 0, 0, SDL_ALPHA_OPAQUE);

 //    SDL_RenderDrawRect(Game::GetInstance().GetRenderer(), &dstRect);

 //    //go back to gray for background rendering 
	// SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 200, 200, 200, SDL_ALPHA_OPAQUE);
}

bool Collider::Is(std::string type)
{
    return (type == "Collider");
}

void Collider::SetScale(Vec2 scale)
{
    m_scale = scale;
}

void Collider::SetOffset(Vec2 offset)
{
    m_offset = offset;
}


void Collider::solveWallCollision(Helper::Direction directionX, Helper::Direction directionY, GameObject *associated, Collider* playerCollider, Collider* wall, Vec2 speed)
{
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

    // printf("-------- Wall Collision ----------: \n");
    // printf("\tplayerBoxCoords = (%f , %f, %f , %f)\n", pLeftX, pRightX, pTopY, pBottomY);
    // printf("\twallBoxCoords = (%f , %f, %f , %f)\n", wallLeftX, wallRightX, wallTopY, wallBottomY);

    // printf("\toverlap = (%f ; %f)\n", overlap.x(), overlap.y());
    // printf("\tspeed = (%f ; %f)\n", speed.x(), speed.y());
    if(overlap.x() > overlap.y())
    {
        if(directionY == Helper::Direction::UP)
        {
            //player is moving down
            float oldY = pBox.y();
            float newY = wallTopY - pHeight - 1.0f; 
            pBox.setY(newY);

            float displacement = fabs(oldY - newY);
            // printf("\t(oldY, newY) : (%f ; %f)\n", oldY, newY);
            // printf("\t oldPos = (%f, %f)\n", associated->m_pos.x(), associated->m_pos.y());
            associated->m_pos -= Vec2(0.0f, displacement); 
            // printf("\t newPos = (%f, %f)\n", associated->m_pos.x(), associated->m_pos.y());
        }
        else
        {
            //player is moving up
            float oldY = pBox.y();
            float newY = wallBottomY + 1.0f; 
            pBox.setY(newY);

            float displacement = fabs(oldY - newY);
            // printf("\t(oldY, newY) : (%f ; %f)\n", oldY, newY);
            // printf("\t oldPos = (%f, %f)\n", associated->m_pos.x(), associated->m_pos.y());
            associated->m_pos += Vec2(0.0f, displacement); 
            // printf("\tnewPos = (%f, %f)\n", associated->m_pos.x(), associated->m_pos.y());
                
        }
    }
    else
    {
        // if(speed.x() > 0)
        if(directionX == Helper::Direction::RIGHT)
        {
            //player is moving right
            float oldX = pBox.x();
            float newX = wallLeftX - pWidth - 1.0f; 
            pBox.setX(newX);

            float displacement = fabs(oldX - newX);
            // printf("\t(oldX, newX) : (%f ; %f)\n", oldX, newX);
            // printf("\t oldPos = (%f, %f)\n", associated->m_pos.x(), associated->m_pos.y());
            associated->m_pos -= Vec2(displacement, 0); 
            // printf("\t newPos = (%f, %f)\n", associated->m_pos.x(), associated->m_pos.y());
        }
        else
        {
            //player is moving left
            float oldX = pBox.x();
            float newX = wallRightX + 1.0f; 
            pBox.setX(newX);

            float displacement = fabs(oldX - newX);
            // printf("\t(oldX, newX) : (%f ; %f)\n", oldX, newX);
            // printf("\t oldPos = (%f, %f)\n", associated->m_pos.x(), associated->m_pos.y());
            associated->m_pos += Vec2(displacement, 0); 
            // printf("\t newPos = (%f, %f)\n", associated->m_pos.x(), associated->m_pos.y());
        }
    }

    // printf("-------------------------------");
}
