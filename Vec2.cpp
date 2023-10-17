#include "Vec2.h"

Vec2 rotate(Vec2 v, float deg)
{
    float cs= cosf(DEG2RAD(deg)), sn = sinf(DEG2RAD(deg));
    return Vec2(v.x() * cs - v.y() * sn,
                v.x() * sn + v.y() * cs);
}


