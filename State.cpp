#include "State.h"
#include <SDL/SDL.h>
#include <string>
#include "Vec2.h"
#include "Component.h"
#include "Sound.h"
#include "Game.h"
#include "TileSet.h"
#include "TileMap.h"
#include "Helper.h"
#include "InputManager.h"
#include "Camera.h"
#include "CameraFollower.h"
#include "Collider.h"
#include "Player.h"
#include <algorithm>
#include <set>

State::State()
{
    m_started = false;
    m_quitRequested = false;
}

State::~State()
{
    m_objectArray.clear();
}

bool State::QuitRequested()
{
    return m_quitRequested;
}

void State::LoadAssets()
{
    //add player
    GameObject* playerObj = new GameObject();
    Player* player = new Player(*playerObj);
    playerObj->AddComponent(player);
    playerObj->m_pos = Vec2(SCREEN_WIDTH/2.0f, SCREEN_HEIGHT/2.0f);

    Camera::Follow(AddObject(playerObj));
}

std::weak_ptr<GameObject> State::AddObject(GameObject* go)
{
    if(!go->m_started) go->Start();
    std::shared_ptr<GameObject> obj_ptr(go);
    m_objectArray.push_back(obj_ptr);
    return std::weak_ptr<GameObject>(obj_ptr);
}

std::weak_ptr<GameObject> State::GetObjectPtr(GameObject* go)
{
     for(int i = 0; i < m_objectArray.size(); i++)
    {
        GameObject* ptr = m_objectArray[i].get();
        if(ptr == go) 
            return std::weak_ptr<GameObject>(m_objectArray[i]);
    }
    return std::weak_ptr<GameObject>();
}

void State::Start()
{
    LoadAssets();

    for(auto obj : m_objectArray)
    {
        if(!obj->m_started) 
        {
            obj->Start();
            obj->m_started = true;
        }
    }

    m_started = true;
}


void State::Update(float dt)
{
    Camera::Update(dt);

    //If ESC key is pressed, quit the game
    if(InputManager::GetInstance().IsKeyDown(ESCAPE_KEY))
    {
        m_quitRequested = true;
    }

    //update game objects
    for(int i = 0; i < m_objectArray.size(); i++)
    {
        m_objectArray[i]->Update(dt);
    }
     
    //test for collision
    std::set<int> tested; 
    for(int i = 0; i < m_objectArray.size(); i++)
    {
        Collider* collA = (Collider*) m_objectArray[i]->GetComponent("Collider");
        if(collA != nullptr)
        {
            for(int j = 0; j < m_objectArray.size(); j++)
            {
                Collider* collB = (Collider*) m_objectArray[j]->GetComponent("Collider");
                if(j != i &&
                   collB != nullptr &&
                   tested.find(j) != tested.end())
                {
                    float angleDegA = m_objectArray[i]->m_angleDeg;
                    float angleDegB = m_objectArray[j]->m_angleDeg;
                    if(IsColliding(collA->m_box, collB->m_box, 
                                   angleDegA, angleDegB))
                    {
                        m_objectArray[i]->NotifyCollision(*m_objectArray[j]);
                        m_objectArray[j]->NotifyCollision(*m_objectArray[i]);
                    }
                }
            }
        }
        tested.insert(i);
    }

    //erase dead game objects
    for(int i = m_objectArray.size()-1; i >= 0; i--)
    {
        if(m_objectArray[i].get()->IsDead())
        {
                m_objectArray.erase(m_objectArray.begin() + i);
        }
    }
}

void State::Render()
{
    for(auto obj : m_objectArray)
    {
        obj->Render();
    }
}

