#include "GameObject.h"
#include "Component.h"


GameObject::GameObject()
{
    m_started = false;
    m_isDead = false;
    m_angleDeg = 0.0f;
}

GameObject::~GameObject()
{
    m_components.clear();
}

void GameObject::Start()
{
    for(unsigned int i = 0; i < m_components.size(); i++)
    {
        if(!m_components[i]->m_started)
        {
            m_components[i]->Start();
            m_components[i]->m_started = true;
        }
    }
}

void GameObject::Update(float dt)
{
    for(unsigned int i = 0; i < m_components.size(); i++)
    {
        m_components[i]->Update(dt);
    }
}

void GameObject::Render()
{
    for(unsigned int i = 0; i < m_components.size(); i++)
    {
        m_components[i]->Render();
    }
}
bool GameObject::IsDead()
{
    return m_isDead;
}

void GameObject::RequestDelete()
{
    m_isDead = true;
}

void GameObject::AddComponent(Component* cpt)
{
    if(!cpt->m_started) 
    {
        cpt->Start();
        cpt->m_started = true;
    }
    m_components.emplace_back(cpt);
}

void GameObject::RemoveComponent(Component* cpt)
{
    for(int i = m_components.size()-1; i >= 0; i--)
    {
        if(m_components[i].get() == cpt)
        {
            m_components.erase(m_components.begin()+i);
        }
    }
}

Component* GameObject::GetComponent(std::string cpt)
{
    for(unsigned i = 0; i < m_components.size(); i++)
    {
        if(m_components[i]->Is(cpt))
        {
            return m_components[i].get();
        }
    }
    return nullptr;
}

Vec2 GameObject::GetCenter()
{
    return m_pos + Vec2(m_box.z()/2.0f, m_box.w()/2.0f);
}

void GameObject::NotifyCollision(GameObject& other)
{
    for(int i = 0; i < m_components.size(); i++)
    {
        m_components[i]->NotifyCollision(other);
    }
}
