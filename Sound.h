#pragma once

#include "Component.h"

struct Mix_Chunk;

struct Sound : Component
{
private:
    Mix_Chunk* m_chunk;
    int m_channel;
public:
    Sound(GameObject& associated);
    Sound(GameObject& associated, std::string file);
    ~Sound();
    
    void Start();
    void Play(int times = 1);
    void Stop();
    void Open(std::string file);
    bool IsOpen();
    
    void Update(float dt);
    void Render();
    bool Is(std::string type);
};
