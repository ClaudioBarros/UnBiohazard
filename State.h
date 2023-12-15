#pragma once

#include "Sprite.h"
#include "Music.h" 
#include "GameObject.h"
#include <vector>
#include <memory>
#include <deque>

struct State
{
private: 
    bool m_quitRequested;
    bool m_started;
    std::deque<std::shared_ptr<GameObject>> m_objectArray;
public:

    State();
    ~State();

    std::weak_ptr<GameObject> AddObject(GameObject* go);
    std::weak_ptr<GameObject> GetObjectPtr(GameObject* go);

    void Start();
    void LoadAssets();
    void Update(float dt);
    void Render();
    bool QuitRequested();
};

