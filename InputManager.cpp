#include "InputManager.h"
#include <SDL/SDL.h>

InputManager::InputManager()
{
    for(int i = 0; i < 6; i++) m_mouseState[i] = false;
    for(int i = 0; i < 6; i++) m_mouseUpdate[i] = 0;
    for(int i = 0; i < 416; i++) m_keyState[i] = false;
    for(int i = 0; i < 416; i++) m_keyUpdate[i] = 0;

    m_quitRequested = false;
    m_updateCounter = 0;
    m_mouseX = 0;
    m_mouseY = 0;
}

InputManager::~InputManager(){}

InputManager& InputManager::GetInstance()
{
    static InputManager inst;
    return inst;
}
 
void InputManager::Update()
{
    m_updateCounter++;

	SDL_Event event;

	SDL_GetMouseState(&m_mouseX, &m_mouseY);

    m_quitRequested = false;

	while (SDL_PollEvent(&event)) 
    {
		if(event.type == SDL_QUIT) 
        {
			m_quitRequested = true;
		}

		if(event.type == SDL_MOUSEBUTTONDOWN) 
        {
            m_mouseState[event.button.button] = true;
            m_mouseUpdate[event.button.button] = m_updateCounter;
		}
		if(event.type == SDL_MOUSEBUTTONUP) 
        {
            m_mouseState[event.button.button] = false;
            m_mouseUpdate[event.button.button] = m_updateCounter;
        }

		if( event.type == SDL_KEYDOWN ) 
        {
            if(!event.key.repeat)
            {
                if(event.key.keysym.sym >= 0x40000000) 
                {
                    m_keyState[event.key.keysym.sym- 0x3FFFFF81] = true;
                    m_keyUpdate[event.key.keysym.sym - 0x3FFFFF81] = m_updateCounter;
                }
                else
                {
                    m_keyState[event.key.keysym.sym] = true;
                    m_keyUpdate[event.key.keysym.sym] = m_updateCounter;
                }
            }
		}

		if( event.type == SDL_KEYUP) 
        {
            if(!event.key.repeat)
            {
                if(event.key.keysym.sym >= 0x40000000) 
                {
                    m_keyState[event.key.keysym.sym - 0x3FFFFF81] = false;
                    m_keyUpdate[event.key.keysym.sym - 0x3FFFFF81] = m_updateCounter;
                }
                else
                {
                    m_keyState[event.key.keysym.sym] = false;
                    m_keyUpdate[event.key.keysym.sym] = m_updateCounter;
                }
            }
        }
	}

}

bool InputManager::KeyPress(int key)
{
    if(key >= 0x40000000) 
    {
        return (m_keyState[key - 0x3FFFFF81] && 
               m_keyUpdate[key - 0x3FFFFF81] == m_updateCounter);
    }
    else
    {
        return (m_keyState[key] && 
                m_keyUpdate[key] == m_updateCounter);
    }
}

bool InputManager::KeyRelease(int key)
{
    if(key >= 0x40000000) 
    {
        return (!m_keyState[key - 0x3FFFFF81] && 
                 m_keyUpdate[key -0x3FFFFF81] == m_updateCounter);
    }
    else
    {
        return (!m_keyState[key] && 
                 m_keyUpdate[key] == m_updateCounter);
    }
}

bool InputManager::IsKeyDown(int key)
{
    if(key >= 0x40000000) 
        return m_keyState[key - 0x3FFFFF81];
    else
        return m_keyState[key];
}

bool InputManager::MousePress(int button)
{
    return (m_mouseState[button] && 
            m_mouseUpdate[button] == m_updateCounter);
}
bool InputManager::MouseRelease(int button)
{
    return (!m_mouseState[button] && 
             m_mouseUpdate[button] == m_updateCounter);
}
bool InputManager::IsMouseDown(int button)
{
    return m_mouseState[button];
}

int InputManager::GetMouseX()
{
    return m_mouseX; 
}

int InputManager::GetMouseY()
{
    return m_mouseY;
}

bool InputManager::QuitRequested()
{
    return m_quitRequested;
}

