#include "Gato.h"
#include "Player.h"
#include "Sprite2.h"
#include "Camera.h"
#include "InputManager.h"
#include "Game.h"
#include "Collider.h"
#include "Helper.h"

Gato::Gato(GameObject& associated) : Component(associated)
{
    float idleFrameTime = 0.2;
    int numIdleFrames = 6;

    m_sptIdle = new Sprite2(associated, 
                    getAbsPath("/assets/img/gato_mercador.png"),
                    numIdleFrames,
                    idleFrameTime,
                    true);
    m_sptIdle->SetScale(2.0f, 2.0f);
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

Gato::~Gato(){}

void Gato::Start(){}

void Gato::Update(float dt){}


void Gato::Render(){}

bool Gato::Is(std::string type)
{
    return (type == "Gato");
}

void Gato::NotifyCollision(GameObject& other){}



