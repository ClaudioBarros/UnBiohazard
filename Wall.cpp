#include "Wall.h"
#include "Collider.h"

Wall::Wall(GameObject& associated, Vec2 dimensions, Vec2 pos) : Component(associated)
{
    m_associated.m_pos = pos;
    m_associated.m_box = Rect((uint32_t)pos.x(), 
                              (uint32_t)pos.y(), 
                              (uint32_t)dimensions.x(),
                              (uint32_t)dimensions.y());

    m_collider = new Collider(associated);
    m_associated.AddComponent(m_collider);
    m_associated.AddComponent(this);
}

Wall::~Wall()
{
}

void Wall::Start()
{
}

void Wall::Update(float dt)
{
}

void Wall::Render()
{
}

bool Wall::Is(std::string type)
{
    return (type == "Wall");
}

void Wall::NotifyCollision(GameObject& other)
{

}

