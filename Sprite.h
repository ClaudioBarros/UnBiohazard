#pragma once 

#include <SDL/SDL.h>
#include <SDL_image/SDL_image.h>
#include "Component.h"
#include "Vec2.h"
#include "Timer.h"

struct Sprite : Component
{
private:    
    SDL_Texture* m_texture;
    int m_width;
    int m_height;
    SDL_Rect m_clipRect;
    Vec2 m_scale;

    unsigned m_frameCount;
    unsigned m_currFrame;
    unsigned m_frameWidth;
    unsigned m_frameHeight;
    float m_frameTime;
    float m_secondsToSelfDestruct;
    Timer m_selfDestructCount;

public: 
    Sprite(GameObject& associated, 
           std::string file, 
           int frameCount = 1,
           float frameTime = 1.0f,
           float secondsToSelfDestruct = 0.0f);
    ~Sprite();

    float m_timeElapsed;

    void Start();
    void Open(std::string file);
    void SetClip(int x, int y, int w, int h);
    void Render(int x, int y);
    void Render();
    void Update(float dt);
    
    void SetFrame(int frame);
    void SetFrameCount(int frameCount);
    void SetFrameTime(float frameTime);
    unsigned GetCurrFrame();
    
    bool IsOpen();

    int GetWidth();
    int GetHeight();
    Vec2 GetScale();
    void SetScale(float scaleX, float scaleY);

    bool Is(std::string type);
};
