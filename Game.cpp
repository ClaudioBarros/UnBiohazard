#include "Game.h"

#include <SDL_image/SDL_image.h>
#include <SDL_mixer/SDL_mixer.h>
#include "InputManager.h"
#include <cstdlib>
#include <ctime>

Game::Game()
{
    //init SDL 
    if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) != 0) 
    {
        printf("Failed to initialize SDL: %s\n", SDL_GetError());
        exit(1);
    }

    //Init window
    int windowFlags = 0;
    m_window = SDL_CreateWindow(GAME_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, windowFlags );
    if(!m_window)
    {
        printf("Failed to create window: %s\n", SDL_GetError());
        exit(1);
    }

    //Init renderer
    int rendererFlags = SDL_RENDERER_ACCELERATED;
    m_renderer = SDL_CreateRenderer(this->m_window, -1, rendererFlags);
    if(!m_renderer)
    {
        printf("Failed to create renderer: %s\n", SDL_GetError());
        exit(1);
    }

    //init SDL image
    int imgInitFlags = (IMG_INIT_PNG | IMG_INIT_JPG);
    if(IMG_Init(imgInitFlags) != imgInitFlags)
    {
        printf("Failed to initialize SDL_Image: %s\n", IMG_GetError());
        exit(1);
    }

    //init SDL Mixer
    int mixerFlags = MIX_INIT_FLAC|MIX_INIT_OGG;
    if((Mix_Init(mixerFlags) & mixerFlags) != (mixerFlags))
    {
        printf("Failed to initialize SDL_Mixer: %s\n", Mix_GetError());
        exit(1);
    }
    if(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) != 0)
    {
        printf("Failed to initialize SDL_Mixer: %s\n", Mix_GetError());
        exit(1);
    }

    //init Resources
    m_resources = new Resources();

    srand(time(NULL));

    SDL_SetRenderDrawColor(m_renderer, 200, 200, 200, 255);

    //init member variables
    m_dt = 0.0f;
    m_frameStart = 0;
}

Game::~Game()
{
    //close SDL_Mixer
    Mix_CloseAudio();
    Mix_Quit();

    //close SDL Image
    IMG_Quit();

    //close renderer
    SDL_DestroyRenderer(m_renderer);

    //close window
    SDL_DestroyWindow(m_window);

    //close SDL
    SDL_Quit();
}

Game* Game::m_instance = 0;

Game& Game::GetInstance()
{
    if(m_instance == nullptr)
    {
        m_instance = new Game();
    }

    return *m_instance;
}

State& Game::GetState()
{
    return *m_state; 
}

Resources& Game::GetResources()
{
    return *m_resources;
}

SDL_Renderer* Game::GetRenderer()
{
    return m_renderer;
}

void Game::CalculateDeltaTime()
{
    unsigned currTicks = SDL_GetTicks();
    m_dt = 0.001f * (float)(currTicks - m_frameStart);
    m_frameStart = currTicks;
}

float Game::GetDeltaTime()
{
    return m_dt;
}

void Game::Run()
{
    m_state = new State();

    m_state->Start();

    while(!m_state->QuitRequested())
    {
        SDL_RenderClear(m_renderer);
        CalculateDeltaTime();
        InputManager::GetInstance().Update();
        m_state->Update(m_dt);
        m_state->Render();
        SDL_RenderPresent(m_renderer);

        SDL_Delay(16);
    }
}


