#ifndef VEC2_H
#define VEC2_H

#include "math_types.h"

// Return Vec2 created
LFINLINE Vec2 vec2_create(f32 x, f32 y)
{ return (Vec2){x, y}; }

// Return Vec2(0.0f, 0.0f)
LFINLINE Vec2 Vec2_zero()
{ return (Vec2){0.0f, 0.0f}; }

// Return Vec2(1.0f, 1.0f)
LFINLINE Vec2 Vec2_one()
{ return (Vec2){1.0f, 1.0f}; }

// Return Vec2(0.0f, 1.0f)
LFINLINE Vec2 Vec2_up()
{ return (Vec2){0.0f, 1.0f}; }

// Return Vec2(0.0f, -1.0f)
LFINLINE Vec2 Vec2_down()
{ return (Vec2){0.0f, -1.0f}; }

// Return Vec2(1.0f, 0.0f)
LFINLINE Vec2 Vec2_right()
{ return (Vec2){1.0f, 0.0f}; }

// Return Vec2(-1.0f, 0.0f)
LFINLINE Vec2 Vec2_left()
{ return (Vec2){-1.0f, 0.0f}; }

#endif // VEC2_H