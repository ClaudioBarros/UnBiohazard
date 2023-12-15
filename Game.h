#pragma once

#include <SDL/SDL.h>
#include "State.h"
#include "Resources.h"

#define GAME_TITLE "UnBiohazard"
#define SCREEN_WIDTH 1280 
#define SCREEN_HEIGHT 720 
#define MAX_SOUND_CHANNELS 32

struct Game
{
private:

    Game(); 

    static Game* m_instance;
    SDL_Window* m_window;
    SDL_Renderer* m_renderer;
    Resources* m_resources;
    State* m_state;

    int m_frameStart;
    float m_dt; //in seconds
    void CalculateDeltaTime();

public:

    ~Game();

    void Run();
    static Game& GetInstance();
    State& GetState();
    Resources& GetResources();
    SDL_Renderer* GetRenderer();

    float GetDeltaTime();
};

