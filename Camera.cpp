#include "Camera.h"
#include "Game.h"
#include "GameObject.h"
#include "InputManager.h"
#include <memory>

Vec2 Camera::m_pos = Vec2(0.0f, 0.0f);
float Camera::m_speed = 250.0f;
std::weak_ptr<GameObject> Camera::m_focus = std::weak_ptr<GameObject>();

void Camera::Update(float dt)
{
    //camera has no focus for now
    if(!m_focus.expired())
    {
        Vec2 center = m_focus.lock()->GetCenter();
        m_pos = center - Vec2(SCREEN_WIDTH/2.0f, SCREEN_HEIGHT/2.0f);
    }
    else
    {

        float speed = m_speed * dt;
         
        if(InputManager::GetInstance().IsKeyDown(UP_ARROW_KEY))
        {
             m_pos -= Vec2(0, speed);
        }

        if(InputManager::GetInstance().IsKeyDown(DOWN_ARROW_KEY))
        {
            m_pos += Vec2(0, speed);
        }
        
        if(InputManager::GetInstance().IsKeyDown(LEFT_ARROW_KEY))
        {
            m_pos -= Vec2(speed, 0);
        }

        if(InputManager::GetInstance().IsKeyDown(RIGHT_ARROW_KEY))
        {
            m_pos += Vec2(speed, 0);
        }
        
    }
}

void Camera::Unfollow()
{
    m_focus = std::weak_ptr<GameObject>();
}

void Camera::Follow(std::weak_ptr<GameObject> newFocus)
{
    m_focus = newFocus;
}

