#pragma once

#include "Vec2.h"
#include <memory>

//forward declarations
struct GameObject;

struct Camera
{
private:
    static std::weak_ptr<GameObject> m_focus;

public:

    static Vec2 m_pos;
    static float m_speed; //units per second

    static void Update(float dt);
    static void Unfollow();
    static void Follow(std::weak_ptr<GameObject> newFocus);
};

