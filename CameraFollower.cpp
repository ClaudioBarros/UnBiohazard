#include "CameraFollower.h"
#include "Camera.h"
#include <cstring>

CameraFollower::CameraFollower(GameObject& go) : Component(go)
{
}

void CameraFollower::Start(){}

void CameraFollower::Update(float dt)
{
    m_associated.m_pos = Camera::m_pos;
}

void CameraFollower::Render()
{
}

bool CameraFollower::Is(std::string type)
{
    return (type == "CameraFollower");
}
