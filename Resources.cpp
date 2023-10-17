#include "Resources.h"
#include "Game.h"

SDL_Texture* Resources::GetImage(std::string file)
{
    SDL_Texture* imgPtr; 
    auto it = m_imageTable.find(file);
    if(it != m_imageTable.end())  
    {
        imgPtr = it->second;
    }
    else
    {
        imgPtr = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str());
        if(imgPtr) 
            m_imageTable.insert({file, imgPtr});
        else 
            printf("Failed texture loading at path %s: %s\n", file.c_str(), IMG_GetError());
    }
    return imgPtr;
}

void Resources::ClearImages()
{
    for(auto img : m_imageTable)
    {
        SDL_DestroyTexture(img.second);
    }
    m_imageTable.clear();
}

Mix_Music* Resources::GetMusic(std::string file)
{
    Mix_Music* musicPtr;
    auto it = m_musicTable.find(file);
    if(it != m_musicTable.end())
    {
        musicPtr = it->second;
    }
    else
    {
        musicPtr = Mix_LoadMUS(file.c_str());
        if(musicPtr)
            m_musicTable.insert({file, musicPtr});
        else
            printf("Failed music loading at path \"%s\" : %s\n", file.c_str(), Mix_GetError());
    }
    return musicPtr;
}

void Resources::ClearMusics()
{
    Mix_FadeOutMusic(0);
    for(auto m : m_musicTable)
    {
        Mix_FreeMusic(m.second);
    }
}

Mix_Chunk* Resources::GetSound(std::string file)
{
    Mix_Chunk* soundPtr;
    auto it = m_soundTable.find(file);
    if(it != m_soundTable.end())
    {
        soundPtr = it->second;
    }
    else
    {
        soundPtr = Mix_LoadWAV(file.c_str());
        if(soundPtr)
            m_soundTable.insert({file, soundPtr});
        else
            printf("Failed sound file loading at path \"%s\" : %s\n", file.c_str(), Mix_GetError());
    }
    return soundPtr;
}

void Resources::ClearSounds() 
{
    for(auto m : m_soundTable)
    {
        Mix_FreeChunk(m.second);
    }
}

