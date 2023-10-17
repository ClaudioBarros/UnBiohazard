#include <Music.h>
#include "Game.h"

Music::Music()
{
    m_music = nullptr; 
}

Music::Music(std::string file)
{
    m_music = nullptr;
    this->Open(file);
}

Music::~Music(){}

void Music::Start(){}

void Music::Play(int times)
{
    if(m_music)
    {
        Mix_PlayMusic(m_music, times);
    }
}

void Music::Stop(int msToStop)
{
    Mix_FadeOutMusic(msToStop);
}

void Music::Open(std::string file)
{
    m_music = Game::GetInstance().GetResources().GetMusic(file);
}

bool Music::IsOpen()
{
    return (m_music != nullptr);
}
