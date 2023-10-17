#pragma once

#include <SDL/SDL.h>

#define LEFT_ARROW_KEY SDLK_LEFT
#define RIGHT_ARROW_KEY SDLK_RIGHT
#define UP_ARROW_KEY SDLK_UP
#define DOWN_ARROW_KEY SDLK_DOWN
#define ESCAPE_KEY SDLK_ESCAPE
#define LEFT_MOUSE_BUTTON SDL_BUTTON_LEFT
#define RIGHT_MOUSE_BUTTON SDL_BUTTON_RIGHT
#define SPACE_KEY SDLK_SPACE

#define KEY_W SDLK_w
#define KEY_A SDLK_a
#define KEY_S SDLK_s
#define KEY_D SDLK_d

struct InputManager
{
private:
    bool m_mouseState[6];
    int m_mouseUpdate[6];
    bool m_keyState[416];
    int m_keyUpdate[416];
    bool m_quitRequested;
    int m_updateCounter;
    int m_mouseX;
    int m_mouseY;

    InputManager();
    ~InputManager();
     
public:
    void Update();

    bool KeyPress(int key);
    bool KeyRelease(int key);
    bool IsKeyDown(int key);

    bool MousePress(int button);
    bool MouseRelease(int button);
    bool IsMouseDown(int button);

    int GetMouseX();
    int GetMouseY();

    bool QuitRequested();

    static InputManager& GetInstance();
};
