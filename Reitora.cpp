#include "Reitora.h"
#include "Player.h"
#include "Sprite2.h"
#include "Camera.h"
#include "InputManager.h"
#include "Game.h"
#include "Collider.h"
#include "Sound.h"
#include "Helper.h"

Reitora::Reitora(GameObject& associated) : Component(associated)
{
    float idleFrameTime = 0.3;
    int numIdleFrames = 2;

    m_sptIdle = new Sprite2(associated, 
                    getAbsPath("/assets/img/reitora_atacada.png"),
                    numIdleFrames,
                    idleFrameTime,
                    true);
    m_sptIdle->SetScale(1.8f, 1.8f);
    m_associated.AddComponent(m_sptIdle);

    // m_sptUnderAttack = new Sprite2(associated, 
    //                 getAbsPath("/assets/img/reitora_atacada.png"),
    //                 numIdleFrames,
    //                 idleFrameTime,
    //                 false);
    // m_sptIdle->SetScale(3.0f, 3.0f);
    // m_associated.AddComponent(m_sptUnderAttack);


    m_collider = new Collider(associated);
    m_associated.AddComponent(m_collider);

    m_state = RESTING; 
}

Reitora::~Reitora(){}

void Reitora::Start(){}

void Reitora::Update(float dt){}


void Reitora::Render(){}

bool Reitora::Is(std::string type)
{
    return (type == "Reitora");
}

void Reitora::NotifyCollision(GameObject& other){}


