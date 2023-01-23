#ifndef MATH_TYPES_H
#define MATH_TYPES_H

#include "core/defines.h"

// #include <intrin.h>
#include <x86intrin.h>

// Vec2 structure
typedef union Vec2_u
{
    f32 elements[2];
    struct
    {
        union
        {
            f32 x, s, u; 
        };
        union
        {
            f32 y, t, v;
        };
    };
} Vec2;

// Vec3 structure
typedef union Vec3_u
{
    f32 elements[3];
    struct
    {
        union
        {
            f32 x, r, s, u; 
        };
        union
        {
            f32 y, g, t, v;
        };
        union
        {
            f32 z, b, p, w;
        };
    };
} Vec3;

// Vec4 structure
typedef union Vec4_u
{
    f32 elements[4];
    struct
    {
        union
        {
            f32 x, r, s; 
        };
        union
        {
            f32 y, g, t;
        };
        union
        {
            f32 z, b, p;
        };
        union
        {
            f32 w, a, q;
        };
    };
} Vec4;

// Mat4 structure
typedef struct MMat4
{
    f32 data[16];
} MMat4;

typedef struct Mat4 {
	union {
		__m256 chunk[2];
		__m128 column[4];
		Vec4 column_vector[4];
		float data[16];
	};
} Mat4;

#endif // MATH_TYPES_H