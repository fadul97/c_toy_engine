#ifndef VEC4_H
#define VEC4_H

#include "math_types.h"

LFINLINE Vec4 vec4_create(f32 x, f32 y, f32 z, f32 w)
{ return (Vec4){x, y, z, w}; }

LFINLINE Vec4 vec4_red()
{ return (Vec4){1.0f, 0.0f, 0.0f, 1.0f}; }

LFINLINE Vec4 vec4_green()
{ return (Vec4){0.0f, 1.0f, 0.0f, 1.0f}; }

LFINLINE Vec4 vec4_blue()
{ return (Vec4){0.0f, 0.0f, 1.0f, 1.0f}; }

#endif // VEC4_H