#pragma once

#include "Component.h"
#include "GameObject.h"

struct CameraFollower : Component
{
    CameraFollower(GameObject& go);

    void Start();
    void Update(float dt);
    void Render();
    bool Is(std::string type);
};
