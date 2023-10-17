#pragma once

struct Timer
{
    float time;
    Timer();
    void Update(float dt);
    void Restart();
};
