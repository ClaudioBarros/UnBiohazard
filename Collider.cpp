#include "Collider.h"    
#include "Camera.h"
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
    
    Vec2 center = getRectCenter(m_associated.m_box);
    Vec2 offset = center + rotate(m_offset, m_associated.m_angleDeg);
}

void Collider::Render()
{
#if 1
    Vec2 center = getRectCenter(m_box);
	SDL_Point points[5];

	Vec2 point = rotate(Vec2(m_box.x(), m_box.y()) - center,
                        m_associated.m_angleDeg)
				 + center - Camera::m_pos;
	points[0] = {(int)point.x(), (int)point.y()};
	points[4] = {(int)point.x(), (int)point.y()};
	
	point = rotate(Vec2(m_box.x() + m_box.z(), m_box.y()) - center, 
                   m_associated.m_angleDeg)
			+ center - Camera::m_pos;

	points[1] = {(int)point.x(), (int)point.y()};
	
	point = rotate(Vec2(m_box.x() + m_box.w(), m_box.y() + m_box.w()) - center, m_associated.m_angleDeg)
			+ center - Camera::m_pos;

	points[2] = {(int)point.x(), (int)point.y()};
	
	point = rotate(Vec2(m_box.x(), m_box.y() + m_box.w())- center,
                   m_associated.m_angleDeg)
			+ center - Camera::m_pos;

	points[3] = {(int)point.x(), (int)point.y()};

	SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 255, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLines(Game::GetInstance().GetRenderer(), points, 5);

	SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 200, 200, 200, SDL_ALPHA_OPAQUE);
#endif
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


