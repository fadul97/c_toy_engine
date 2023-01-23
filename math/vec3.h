#ifndef VEC3_H
#define VEC3_H

#include "math_types.h"

#include <math.h>
#include <stdio.h>

// Return Vec3 created
LFINLINE Vec3 vec3_create(f32 x, f32 y, f32 z)
{ return (Vec3){x, y, z}; }

// Return Vec3(0.0f, 0.0f, 0.0f)
LFINLINE Vec3 vec3_zero()
{ return (Vec3){0.0f, 0.0f, 0.0f}; }

// Return Vec3(1.0f, 1.0f)
LFINLINE Vec3 vec3_one()
{ return (Vec3){1.0f, 1.0f}; }

// Return Vec3(0.0f, 1.0f, 0.0f)
LFINLINE Vec3 vec3_up()
{ return (Vec3){0.0f, 1.0f, 0.0f}; }

// Return Vec3(0.0f, -1.0f, 0.0f)
LFINLINE Vec3 vec3_down()
{ return (Vec3){0.0f, -1.0f, 0.0f}; }

// Return Vec3(1.0f, 0.0f, 0.0f)
LFINLINE Vec3 vec3_right()
{ return (Vec3){1.0f, 0.0f, 0.0f}; }

// Return Vec3(-1.0f, 0.0f, 0.0f)
LFINLINE Vec3 vec3_left()
{ return (Vec3){-1.0f, 0.0f, 0.0f}; }

// Return Vec3(0.0f, 0.0f, -1.0f)
LFINLINE Vec3 vec3_forward()
{ return (Vec3){0.0f, 0.0f, -1.0f}; }

// Return Vec3(0.0f, 0.0f, 1.0f)
LFINLINE Vec3 vec3_back()
{ return (Vec3){0.0f, 0.0f, 1.0f}; }

// Return 'new' Vec3 b added to a
LFINLINE Vec3 vec3_add(Vec3 a, Vec3 b)
{ return (Vec3){a.x + b.x, a.y + b.y, a.z + b.z}; }

// Add Vec3 a and b
LFINLINE void vec3v_add(Vec3 a, Vec3 b)
{
    Vec3 *v = &a;
    v->x += b.x;
    v->y += b.y;
    v->z += b.z;
}

// Return 'new' Vec3 a subtracted by b
LFINLINE Vec3 vec3_minus(Vec3 a, Vec3 b)
{ return (Vec3){a.x - b.x, a.y - b.y, a.z - b.z}; }

// Subtract Vec3 b from a
LFINLINE void vec3v_minus(Vec3 a, Vec3 b)
{
    Vec3 *v = &a;
    v->x -= b.x;
    v->y -= b.y;
    v->z -= b.z;
}

// Return 'new' Vec3 a multiplied by b
LFINLINE Vec3 vec3_multiply(Vec3 a, Vec3 b)
{ return (Vec3){a.x * b.x, a.y * b.y, a.z * b.z}; }

// Multiply Vec3 a and b
LFINLINE void vec3v_multiply(Vec3 a, Vec3 b)
{
    Vec3 *v = &a;
    v->x *= b.x;
    v->y *= b.y;
    v->z *= b.z;
}

// Return 'new' Vec3 a divided by b
LFINLINE Vec3 vec3_divide(Vec3 a, Vec3 b)
{ return (Vec3){a.x / b.x, a.y / b.y, a.z / b.z}; }

// Divide Vec3 a by b
LFINLINE void vec3v_divide(Vec3 a, Vec3 b)
{
    Vec3 *v = &a;
    v->x /= b.x;
    v->y /= b.y;
    v->z /= b.z;
}

// Return Vec3 a multiplied by scalar k
LFINLINE Vec3 vec3_multiply_by_scalar(Vec3 a, f32 k)
{ return (Vec3){a.x * k, a.y * k, a.z * k}; }

// Multiply Vec3 a by scalar k
LFINLINE void vec3v_multiply_by_scalar(Vec3 a, f32 k)
{
    Vec3 *v = &a;
    v->x *= k;
    v->y *= k;
    v->z *= k;
}

// Return Vec3 a divided by scalar k
LFINLINE Vec3 vec3_divide_by_scalar(Vec3 a, f32 k)
{ return (Vec3){a.x / k, a.y / k, a.z / k}; }

// Divide Vec3 a by scalar k
LFINLINE void vec3v_divide_by_scalar(Vec3 a, f32 k)
{
    Vec3 *v = &a;
    v->x /= k;
    v->y /= k;
    v->z /= k;
}

// Return Vec3 a magnitude/length
LFINLINE d64 vec3_length(Vec3 a)
{ return sqrt((a.x * a.x) + (a.y * a.y) + (a.z * a.z)); }

// Return squared length of Vec3 a
LFINLINE d64 vec3_length_squared(Vec3 a)
{ return (a.x * a.x) + (a.y * a.y) + (a.z * a.z); }

// Return normalized Vec3 a
LFINLINE Vec3 vec3_normalize(Vec3 a)
{ return vec3_divide_by_scalar(a, (f32)vec3_length(a)); }

// Normalize Vec3 a
LFINLINE void vec3v_normalize(Vec3 a)
{ vec3v_divide_by_scalar(a, (f32)vec3_length(a)); }

// Return dot product of a and b
LFINLINE d64 vec3_dot_product(Vec3 a, Vec3 b)
{ return (a.x * b.x) + (a.y * b.y) + (a.z * b.z); }

// Return cross product of Vec3 a and b
LFINLINE Vec3 vec3_cross_product(Vec3 a, Vec3 b)
{ return (Vec3){a.y * b.z - a.z * b.y,
                a.z * b.x - a.x * b.z,
                a.x * b.y - a.y * b.x};
}

// Caculate cross product of Vec3 a and b in Vec3 a
LFINLINE void vec3v_cross_product(Vec3 a, Vec3 b)
{
    Vec3 *v = &a;
    float x = a.y * b.z - a.z * b.y;
	float y = a.z * b.x - a.x * b.z;
	float z = a.x * b.y - a.y * b.x;
	v->x = x;
	v->y = y;
	v->z = z;
}

// Return distance between Vec a and b
LFINLINE d64 vec3_distance(Vec3 a, Vec3 b)
{ return vec3_length(vec3_create(a.x - b.x, a.y - b.y, a.z - b.z)); }

// Return if Vec3 a and b are equal
LFINLINE b8 vec3_is_equal(Vec3 a, Vec3 b)
{ return (a.x == b.x) && (a.y == a.y) && (a.z == b.z); }

// Print Vec3: (x, y);
LFINLINE void vec3_print(Vec3 a)
{ printf("(%f, %f, %f)", a.x, a.y, a.z); }

LFINLINE Vec4 mat4_mult_vec3(Mat4 a, Vec4 b)
{
    Vec4 v;

    // printf("%.2f*%.2f + %.2f*%.2f + %.2f*%.2f + %.2f*%.2f\n",
        // a.data[0] , b.x , a.data[1] , b.y , a.data[2] , b.z , a.data[3] , b.w);
    v.x = a.data[0] * b.x + a.data[1] * b.y + a.data[2] * b.z + a.data[3] * b.w;
    v.y = a.data[4] * b.x + a.data[5] * b.y + a.data[6] * b.z + a.data[7] * b.w;
    v.z = a.data[8] * b.x + a.data[9] * b.y + a.data[10] * b.z + a.data[11] * b.w;
    v.w = a.data[12] * b.x + a.data[13] * b.y + a.data[14] * b.z + a.data[15] * b.w;

    return v;
}

#endif // VEC3_H