#include "Sprite2.h"
#include "Game.h"
#include "Resources.h"
#include "Camera.h"
#include <cassert>
#include <string> 

Sprite2::Sprite2(GameObject& associated, 
               std::string file,
               int frameCount,
               float frameTime,
               bool isRendering) : Component(associated)
{
    m_scale = Vec2(1.0f, 1.0f);
    m_texture = nullptr;
    m_frameCount = frameCount;
    m_frameTime = frameTime;
    m_currFrame = 0;
    m_frameWidth = 0;
    m_frameHeight = 0;
    m_timeElapsed = 0.0f;
    this->Open(file);
}

Sprite2::~Sprite2(){}

void Sprite2::Start(){}

void Sprite2::Open(std::string file)
{
    m_texture = Game::GetInstance().GetResources().GetImage(file);

    if(!m_texture) return;

    SDL_QueryTexture(m_texture, nullptr, nullptr, &m_width, &m_height);

    m_frameWidth = m_width / m_frameCount;
    m_frameHeight = m_height;
    this->SetClip(0, 0, m_frameWidth, m_frameHeight);
}

void Sprite2::SetFrame(int frame)
{
    assert(frame < m_frameCount);
    m_currFrame = frame;

    SetClip(m_currFrame * m_frameWidth, 
            0, //y will always be zero since sprite sheet is linear
            m_frameWidth,
            m_frameHeight);
}

unsigned Sprite2::GetCurrFrame()
{
    return m_currFrame;
}

void Sprite2::SetFrameCount(int frameCount)
{
    m_frameCount = frameCount; 
    m_currFrame = 0;

    m_frameWidth = m_width/m_frameCount;

    SetClip(m_currFrame * m_frameWidth, 
            0, //y will always be zero since sprite sheet is linear
            m_frameWidth,
            m_frameHeight);
    
    m_associated.m_box = Rect(m_associated.m_pos.x(),
                              m_associated.m_pos.y(),
                              m_clipRect.w * m_scale.x(),
                              m_clipRect.h * m_scale.y());
}

void Sprite2::SetFrameTime(float frameTime)
{
    m_frameTime = frameTime;
}

void Sprite2::SetClip(int x, int y, int w, int h)
{
    m_clipRect.x = x;
    m_clipRect.y = y;
    m_clipRect.w = w;
    m_clipRect.h = h;
}

void Sprite2::Render(int x, int y)
{

    SDL_Rect dstRect;
    dstRect.x = (int) x; 
    dstRect.y = (int) y; 
    dstRect.w = (int) m_clipRect.w * m_scale.x(); 
    dstRect.h = (int) m_clipRect.h * m_scale.y();

#if 0 
//Draw object's rects for debugging
    SDL_RenderDrawRect(Game::GetInstance().GetRenderer(), &dstRect);
#endif

    if(m_flipTexture)
    {
        SDL_RenderCopyEx(Game::GetInstance().GetRenderer(),
                         m_texture,
                         &m_clipRect, 
                         &dstRect,
                         m_associated.m_angleDeg,
                         nullptr,
                         SDL_FLIP_HORIZONTAL);

    }
    else
    {
        SDL_RenderCopyEx(Game::GetInstance().GetRenderer(),
                         m_texture,
                         &m_clipRect, 
                         &dstRect,
                         m_associated.m_angleDeg,
                         nullptr,
                         SDL_FLIP_NONE);
    }
}

void Sprite2::Render()
{
    if(!m_isRendering)
        return;

    Render((int) m_associated.m_pos.x() - Camera::m_pos.x(),
           (int) m_associated.m_pos.y()- Camera::m_pos.y());
}

void Sprite2::Update(float dt)
{

    m_timeElapsed += dt;
    if(m_frameCount > 1)
    {
        if(m_timeElapsed >= m_frameTime)
        {
            m_currFrame = (m_currFrame + 1) % m_frameCount;
            m_timeElapsed = 0.0f;
        }
    }
    
    SetClip(m_currFrame * m_frameWidth, 
            0, //y will always be zero since sprite sheet is linear
            m_frameWidth,
            m_frameHeight);

    m_associated.m_box = Rect(m_associated.m_pos.x(),
                              m_associated.m_pos.y(),
                              m_frameWidth *  m_scale.x(),
                              m_frameHeight * m_scale.y());
}

bool Sprite2::Is(std::string type)
{
    return (type == "Sprite2");
}

int Sprite2::GetWidth()
{
    return (int) m_frameWidth * m_scale.x();
}

int Sprite2::GetHeight()
{
    return (int) m_frameWidth * m_scale.y(); 
}

Vec2 Sprite2::GetScale()
{
    return m_scale;
}

void Sprite2::SetScale(float scaleX, float scaleY)
{
    m_scale = Vec2(scaleX, scaleY);
}

bool Sprite2::IsOpen()
{
    return (m_texture != nullptr);
}

