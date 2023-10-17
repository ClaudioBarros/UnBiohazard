#pragma once

#include <unordered_map>
#include <SDL_mixer/SDL_mixer.h>
#include <SDL_image/SDL_image.h>
#include <string>

struct Resources
{
    std::unordered_map<std::string , SDL_Texture*> m_imageTable;
    std::unordered_map<std::string , Mix_Music*> m_musicTable;
    std::unordered_map<std::string , Mix_Chunk*> m_soundTable;

public:
    SDL_Texture* GetImage(std::string file);
    void ClearImages();

    Mix_Music* GetMusic(std::string file);
    void ClearMusics();

    Mix_Chunk* GetSound(std::string file);
    void ClearSounds() ;
};
