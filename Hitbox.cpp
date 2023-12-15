#include "Hitbox.h"
#include "Collider.h"

Hitbox::Hitbox(GameObject& associated, Vec2 pos, Vec2 dimensions, Vec2 scale, Vec2 offset) : Component(associated)
{
    m_associated.m_box = Rect((uint32_t)pos.x(), 
                              (uint32_t)pos.y(), 
                              (uint32_t)dimensions.x(),
                              (uint32_t)dimensions.y());

    m_collider = new Collider(associated, scale, offset);
    m_associated.AddComponent(m_collider);
    m_associated.AddComponent(this);
}

Hitbox::~Hitbox()
{
}

void Hitbox::Start()
{
}

void Hitbox::Update(float dt)
{

}

void Hitbox::Render()
{

}

bool Hitbox::Is(std::string type)
{
    return (type == "Hitbox");
}

void Hitbox::NotifyCollision(GameObject& other)
{

}


