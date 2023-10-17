#ifndef MUSIC_H
#define MUSIC_H

#include <SDL_mixer/SDL_mixer.h>
#include <string>

struct Music
{
private: 
    Mix_Music* m_music;

public:
    Music();
    Music(std::string file);
    ~Music();

    void Start();
    void Play(int times=-1);
    void Stop(int msToStop = 1500);
    void Open(std::string file);
    bool IsOpen();
};

#endif // !MUSIC_H
