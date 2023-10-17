#pragma once 

#include "Sound.h"
#include "Game.h"
#include <SDL_mixer/SDL_mixer.h>
#include <cstring> 
#include <cstdio>

Sound::Sound(GameObject& associated) : Component(associated) 
{
    m_chunk = nullptr;
}

Sound::Sound(GameObject& associated, std::string file) : Sound(associated)
{
    Open(file);
}

Sound::~Sound(){}

void Sound::Play(int times)
{
    m_channel = Mix_PlayChannel(-1, m_chunk, times);
}

void Sound::Stop()
{
    if(m_chunk != nullptr)
    {
        Mix_HaltChannel(m_channel);
    }
}

void Sound::Open(std::string file)
{
    m_chunk = Game::GetInstance().GetResources().GetSound(file);
}

bool Sound::IsOpen()
{
    return (m_chunk != nullptr) ;
}

void Sound::Start(){}

void Sound::Update(float dt){}

void Sound::Render(){}

bool Sound::Is(std::string type)
{
    return (type == "Sound");
}
