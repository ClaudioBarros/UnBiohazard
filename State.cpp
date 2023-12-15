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
#include "Wall.h"
#include <algorithm>
#include <set>
#include "cute_tiled.h"
#include "Pigeon.h"
#include "Reitora.h"
#include "Gato.h"
#include "Sarue.h"

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
    Vec2 bgScale(1.5f, 1.5f);

    //add background
    GameObject* bgObj = new GameObject();
    Sprite2* bg = new Sprite2(*bgObj, getAbsPath("/assets/map/ceubinho.png"));
    bg->SetScale(bgScale.x(), bgScale.y());
    bgObj->AddComponent(bg);
    bgObj->m_pos = Vec2(0.0f, 0.0f);
    AddObject(bgObj);

    // std::string tiledMap = getAbsPath("/assets/map/testmap.tmj");
    // cute_tiled_map_t* map = cute_tiled_load_map_from_file(tiledMap.c_str(), nullptr);

    //add walls 
    //wall1
    {
        GameObject* wallObj = new GameObject();
        Vec2 wallDim = Vec2(411.0f, 481.0f) * bgScale;
        Vec2 wallPos = Vec2(0.0f, 0.0f);
        Wall* wall = new Wall(*wallObj, wallDim, wallPos);
        AddObject(wallObj);
    }
    //wall2
    {
        GameObject* wallObj = new GameObject();
        Vec2 wallDim = Vec2(561.0f , 481.0f) * bgScale;
        Vec2 wallPos = Vec2(954.0f, 0.0f) * bgScale;
        Wall* wall = new Wall(*wallObj, wallDim, wallPos);
        AddObject(wallObj);
    }
    //wall3
    {
        GameObject* wallObj = new GameObject();
        Vec2 wallDim = Vec2(404.0f , 264.0f) * bgScale;
        Vec2 wallPos = Vec2(0.0f, 563.0f) * bgScale;
        Wall* wall = new Wall(*wallObj, wallDim, wallPos);
        AddObject(wallObj);
    }
    //wall4 
    {
        GameObject* wallObj = new GameObject();
        Vec2 wallDim = Vec2(548.0f , 280.0f) * bgScale;
        Vec2 wallPos = Vec2(969.0f, 563.0f) * bgScale;
        Wall* wall = new Wall(*wallObj, wallDim, wallPos);
        AddObject(wallObj);
    }
    //frangao
    {
        GameObject* wallObj = new GameObject();
        Vec2 wallDim = Vec2(180.0f , 175.0f) * bgScale;
        Vec2 wallPos = Vec2(669.0f, 1055.0f) * bgScale;
        Wall* wall = new Wall(*wallObj, wallDim, wallPos);
        AddObject(wallObj);
    }
    //placa unb 1
    {
        GameObject* wallObj = new GameObject();
        Vec2 wallDim = Vec2(61.0f , 47.0f) * bgScale;
        Vec2 wallPos = Vec2(394.0f, 910.0f) * bgScale;
        Wall* wall = new Wall(*wallObj, wallDim, wallPos);
        AddObject(wallObj);
    }
    //placa unb 2
    {
        GameObject* wallObj = new GameObject();
        Vec2 wallDim = Vec2(30.0f , 150.0f) * bgScale;
        Vec2 wallPos = Vec2(411.0f, 832.0f) * bgScale;
        Wall* wall = new Wall(*wallObj, wallDim, wallPos);
        AddObject(wallObj);
    }
   
    //add player
    GameObject* playerObj = new GameObject();
    Player* player = new Player(*playerObj);
    playerObj->AddComponent(player);
    playerObj->m_pos = Vec2(SCREEN_WIDTH/2.0f, SCREEN_HEIGHT/2.0f);

    Camera::Follow(AddObject(playerObj));

    //status bar
    // GameObject* statusBarObj = new GameObject();
    // Vec2 statusDim(SCREEN_WIDTH, 0.1f*SCREEN_HEIGHT);
    // Vec2 statusPos(Camera::m_pos.x(),  Camera::m_pos.y() + (0.2f * SCREEN_HEIGHT));
    // Sprite2* statusSpt = new Sprite2(*statusBarObj, getAbsPath("/assets/img/statusbar.png"));
    // // CameraFollower* cf = new CameraFollower(*statusBarObj);
    // statusBarObj->m_box = Rect(0,0, statusDim.x(), statusDim.y());
    // statusBarObj->m_pos = statusPos;
    // statusBarObj->AddComponent(statusSpt);
    // // statusBarObj->AddComponent(cf);
    // AddObject(statusBarObj);
    
    //reitora
    GameObject* reitoraObj = new GameObject();
    Reitora* reitora = new Reitora(*reitoraObj);
    reitoraObj->AddComponent(reitora);
    reitoraObj->m_pos = Vec2(530.0f, 465.0f) * bgScale;
    AddObject(reitoraObj);

    //Gato
    GameObject* gatoObj = new GameObject();
    Gato* gato = new Gato(*gatoObj);
    gatoObj->AddComponent(gato);
    gatoObj->m_pos = Vec2(910.0f, 914.0f) * bgScale;
    AddObject(gatoObj);
    
    //test pigeon
    GameObject* pigeonObj = new GameObject();
    Pigeon* pigeon = new Pigeon(*pigeonObj, 3.0f);
    pigeonObj->AddComponent(pigeon);
    pigeonObj->m_pos = Vec2(playerObj->m_pos.x() + 100.0f, playerObj->m_pos.y() + 100.0f);
    AddObject(pigeonObj);

    //sarue
    GameObject* sarueObj = new GameObject();
    Sarue* sarue = new Sarue(*sarueObj, 1.5f);
    sarueObj->AddComponent(sarue);
    sarueObj->m_pos = Vec2(playerObj->m_pos.x() + 200.0f, playerObj->m_pos.y() + 200.0f);
    AddObject(sarueObj);

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

