#include "Rect.h"
#include "Vec2.h"
#include <algorithm>

bool contains(Rect& rect, float x, float y)
{
    if((x >= rect.x()) && (x <= (rect.x() + rect.z())) &&
       (y >= rect.y()) && (y <= (rect.y() + rect.w())))
        return true;
    else 
        return false;
}

float2 getRectCenter(Rect& r)
{
    return float2(r.x() + (r.z()/2.0f), 
                  r.y() + (r.w()/2.0f));
}

bool IsColliding(Rect& a, Rect& b, 
                 float angleDegA, float angleDegB)
{
    Vec2 A[] = { Vec2( a.x(), a.y() + a.w() ),
                 Vec2( a.x() + a.z(), a.y() + a.w() ),
                 Vec2( a.x() + a.z(), a.y() ),
                 Vec2( a.x(), a.y() )};

    Vec2 B[] = { Vec2( b.x(), b.y() + b.w() ),
                  Vec2( b.x() + b.z(), b.y() + b.w() ),
                  Vec2( b.x() + b.z(), b.y() ),
                  Vec2( b.x(), b.y() )};

    for (auto& v : A) {
        // v = Rotate(v - a.GetCenter(), angleOfA) + a.GetCenter();
        v = rotate(v - getRectCenter(a), angleDegA) + getRectCenter(a);
    }

    for (auto& v : B) {
        // v = Rotate(v - b.GetCenter(), angleOfB) + b.GetCenter();
        v = rotate(v - getRectCenter(b), angleDegB) + getRectCenter(b);
    }

    Vec2 axes[] = { normalize(A[0] - A[1]), 
                    normalize(A[1] - A[2]), 
                    normalize(B[0] - B[1]), 
                    normalize(B[1] - B[2]) };

    for (auto& axis : axes) {
        float P[4];

        for (int i = 0; i < 4; ++i) P[i] = dot(A[i], axis);

        float minA = *std::min_element(P, P + 4);
        float maxA = *std::max_element(P, P + 4);

        for (int i = 0; i < 4; ++i) P[i] = dot(B[i], axis);

        float minB = *std::min_element(P, P + 4);
        float maxB = *std::max_element(P, P + 4);

        if (maxA < minB || minA > maxB)
            return false;
    }

    return true;
}

