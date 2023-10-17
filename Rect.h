#pragma once

#include "Mathlib.h"

typedef float4 Rect;

bool contains(Rect& rect, float x, float y);

float2 getRectCenter(Rect& r);

//expects angles in radians
bool IsColliding(Rect& a, Rect &b, float angleA, float angleB);






