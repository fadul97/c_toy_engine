#ifndef MAT4_H
#define MAT4_H

#include "math_types.h"

#include "core/memory.h"
#include "vec3.h"

#include <math.h>
#include <stdio.h>

#define LF_DEG2RAD M_PI / 180.0f

LFINLINE Mat4 mat4_identity()
{
    Mat4 m;
    m.column[0] = _mm_setr_ps(1, 0, 0, 0);
    m.column[1] = _mm_setr_ps(0, 1, 0, 0);
    m.column[2] = _mm_setr_ps(0, 0, 1, 0);
    m.column[3] = _mm_setr_ps(0, 0, 0, 1);
    return m;
}

LFINLINE Mat4 mat4_translate(Mat4 a, Vec3 b)
{
    Mat4 *v = &a;

    __m128 c = _mm_setr_ps(v->column[3][0], v->column[3][1], v->column[3][2], v->column[3][3]);
    // printf("%.2f, %.2f, %.2f, %.2f\n", v->column[3][0], v->column[3][1], v->column[3][2], v->column[3][3]);

    // v->column[0] = _mm_setr_ps(1, 0, 0, 0);
    // v->column[0] = _mm_setr_ps(1, 0, 0, 0);
    // v->column[0] = _mm_setr_ps(1, 0, 0, 0);
    v->column[3] = _mm_setr_ps(c[0]+b.x, c[1]+b.y, c[2]+b.z, 1);

    return *v;
}

LFINLINE f32 to_radians(f32 degree)
{
    return degree * LF_DEG2RAD;
}

LFINLINE Mat4 mat4_perspective(f32 fov, f32 aspect_ratio, f32 near_plane, f32 far_plane)
{
    f32 rad = fov * LF_DEG2RAD;

    f32 zoom = tan(rad * 0.5f);

    Mat4 m;
    m.column[0] = _mm_setr_ps((1.0f / zoom * aspect_ratio), 0, 0,  0);
	m.column[1] = _mm_setr_ps(0, (1.0f / zoom), 0,  0);
	m.column[2] = _mm_setr_ps(0, 0, -((far_plane+near_plane)/(far_plane-near_plane)), -1);
	m.column[3] = _mm_setr_ps(0, 0, -((2.0f*far_plane*near_plane)/(far_plane-near_plane)),  0);
    
    return m;
}

LFINLINE Mat4 look_at(Vec3 position, Vec3 target, Vec3 up)
{
    Vec3 forward = vec3_normalize(vec3_minus(target, position));
    Vec3 right = vec3_normalize(vec3_cross_product(forward, up));
    up = vec3_normalize(vec3_cross_product(right, forward));

    // Since I'm not multiplying Vec3 forward by -1, I need to invert its values
    // when passing to the matrix
    Mat4 m;
    m.column[0] = _mm_setr_ps(right.x, up.x, -forward.x, 0);
    m.column[1] = _mm_setr_ps(right.y, up.y, -forward.y, 0);
    m.column[2] = _mm_setr_ps(right.z, up.z, -forward.z, 0);
    m.column[3] = _mm_setr_ps(-vec3_dot_product(right, position), 
        -vec3_dot_product(up, position), vec3_dot_product(forward, position), 1);

    return m;
}

// TODO: Test projection
LFINLINE Mat4 mat4_orthographic(f32 left, f32 right, f32 bottom, f32 top, f32 near_plane, f32 far_plane)
{
    Mat4 m;

    // f32 lr = 1.0f / (left - right);
    // f32 bt = 1.0f / (bottom - top);
    // f32 nf = 1.0f / (near_plane - far_plane);

    /* KOHI */
    f32 lr = 1.0f / (left - right);
    f32 bt = 1.0f / (bottom - top);
    f32 nf = 1.0f / (near_plane - far_plane);

    m.column[0] = _mm_setr_ps(-2.0f * lr, 0, 0, 0);
    m.column[1] = _mm_setr_ps(0, -2.0f * bt, 0, 0);
    m.column[2] = _mm_setr_ps(0, 0, 2.0f * nf, 0);
    m.column[3] = _mm_setr_ps((left + right) * lr, (top + bottom) * bt, (far_plane + near_plane) * nf, 1);
    
    return m;
}

LFINLINE Mat4 mat4_scale(Mat4 a, Vec3 b)
{
    Mat4 m = a;

    m.column[0][0] = a.column[0][0] * b.x;
    m.column[1][1] = a.column[1][1] * b.y;
    m.column[2][2] = a.column[2][2] * b.z;

    return m;
}

// Return MMat4 identity matrix
LFINLINE MMat4 mmat4_identity()
{
    MMat4 m;
    lfzero_memory(m.data, sizeof(f32) * 16);
    m.data[0] = 1.0f;
    m.data[5] = 1.0f;
    m.data[10] = 1.0f;
    m.data[15] = 1.0f;
    return m;
}

// Set MMat4 a to identity matrix
LFINLINE void mmat4v_identity(MMat4 a)
{
    MMat4 *m = &a;
    lfzero_memory(m->data, sizeof(f32) * 16);
    m->data[0] = 1.0f;
    m->data[5] = 1.0f;
    m->data[10] = 1.0f;
    m->data[15] = 1.0f;
}

// Return MMat4 a transposed
LFINLINE MMat4 mmat4_transpose(MMat4 a)
{
    MMat4 m = {0};

    m.data[0] = a.data[0];
    m.data[1] = a.data[4];
    m.data[2] = a.data[8];
    m.data[3] = a.data[12];
    
    m.data[4] = a.data[1];
    m.data[5] = a.data[5];
    m.data[6] = a.data[9];
    m.data[7] = a.data[13];
    
    m.data[8] = a.data[2];
    m.data[9] = a.data[6];
    m.data[10] = a.data[10];
    m.data[11] = a.data[14];
    
    m.data[12] = a.data[3];
    m.data[13] = a.data[7];
    m.data[14] = a.data[11];
    m.data[15] = a.data[15];   

    return m;
}

// Transpose MMat4 a
LFINLINE void mmat4v_transpose(MMat4 a)
{
    MMat4 *m = &a;
    MMat4 aux = a;

    m->data[0] = aux.data[0];
    m->data[1] = aux.data[4];
    m->data[2] = aux.data[8];
    m->data[3] = aux.data[12];
    
    m->data[4] = aux.data[1];
    m->data[5] = aux.data[5];
    m->data[6] = aux.data[9];
    m->data[7] = aux.data[13];
    
    m->data[8] = aux.data[2];
    m->data[9] = aux.data[6];
    m->data[10] = aux.data[10];
    m->data[11] = aux.data[14];
    
    m->data[12] = aux.data[3];
    m->data[13] = aux.data[7];
    m->data[14] = aux.data[11];
    m->data[15] = aux.data[15];   
}

// Return multiplication between MMat4 a and b
LFINLINE MMat4 mmat4_multiply(MMat4 a, MMat4 b)
{
    MMat4 m;
    
    m.data[0] = a.data[0]*b.data[0] + a.data[1]*b.data[4] + a.data[2]*b.data[8] + a.data[3]*b.data[12];
    m.data[1] = a.data[0]*b.data[1] + a.data[1]*b.data[5] + a.data[2]*b.data[9] + a.data[3]*b.data[13];
    m.data[2] = a.data[0]*b.data[2] + a.data[1]*b.data[6] + a.data[2]*b.data[10] + a.data[3]*b.data[14];
    m.data[3] = a.data[0]*b.data[3] + a.data[1]*b.data[7] + a.data[2]*b.data[11] + a.data[3]*b.data[15];

    m.data[4] = a.data[4]*b.data[0] + a.data[5]*b.data[4] + a.data[6]*b.data[8] + a.data[7]*b.data[12];
    m.data[5] = a.data[4]*b.data[1] + a.data[5]*b.data[5] + a.data[6]*b.data[9] + a.data[7]*b.data[13];
    m.data[6] = a.data[4]*b.data[2] + a.data[5]*b.data[6] + a.data[6]*b.data[10] + a.data[7]*b.data[14];
    m.data[7] = a.data[4]*b.data[3] + a.data[5]*b.data[7] + a.data[6]*b.data[11] + a.data[7]*b.data[15];

    m.data[8] = a.data[8]*b.data[0] + a.data[9]*b.data[4] + a.data[10]*b.data[8] + a.data[11]*b.data[12];
    m.data[9] = a.data[8]*b.data[1] + a.data[9]*b.data[5] + a.data[10]*b.data[9] + a.data[11]*b.data[13];
    m.data[10] = a.data[8]*b.data[2] + a.data[9]*b.data[6] + a.data[10]*b.data[10] + a.data[11]*b.data[14];
    m.data[11] = a.data[8]*b.data[3] + a.data[9]*b.data[7] + a.data[10]*b.data[11] + a.data[11]*b.data[15];

    m.data[12] = a.data[12]*b.data[0] + a.data[13]*b.data[4] + a.data[14]*b.data[8] + a.data[15]*b.data[12];
    m.data[13] = a.data[12]*b.data[1] + a.data[13]*b.data[5] + a.data[14]*b.data[9] + a.data[15]*b.data[13];
    m.data[14] = a.data[12]*b.data[2] + a.data[13]*b.data[6] + a.data[14]*b.data[10] + a.data[15]*b.data[14];
    m.data[15] = a.data[12]*b.data[3] + a.data[13]*b.data[7] + a.data[14]*b.data[11] + a.data[15]*b.data[15];

    return m;
}

// FIXME: Test it, I think elem[0][0] will be overwritten and change other results
// Multiply MMat4 a and b in MMat4 a
LFINLINE void mmat4v_multiply(MMat4 a, MMat4 b)
{
    MMat4 *m = &a;
    
    m->data[0] = a.data[0]*b.data[0] + a.data[1]*b.data[4] + a.data[2]*b.data[8] + a.data[3]*b.data[12];
    m->data[1] = a.data[0]*b.data[1] + a.data[1]*b.data[5] + a.data[2]*b.data[9] + a.data[3]*b.data[13];
    m->data[2] = a.data[0]*b.data[2] + a.data[1]*b.data[6] + a.data[2]*b.data[10] + a.data[3]*b.data[14];
    m->data[3] = a.data[0]*b.data[3] + a.data[1]*b.data[7] + a.data[2]*b.data[11] + a.data[3]*b.data[15];

    m->data[4] = a.data[4]*b.data[0] + a.data[5]*b.data[4] + a.data[6]*b.data[8] + a.data[7]*b.data[12];
    m->data[5] = a.data[4]*b.data[1] + a.data[5]*b.data[5] + a.data[6]*b.data[9] + a.data[7]*b.data[13];
    m->data[6] = a.data[4]*b.data[2] + a.data[5]*b.data[6] + a.data[6]*b.data[10] + a.data[7]*b.data[14];
    m->data[7] = a.data[4]*b.data[3] + a.data[5]*b.data[7] + a.data[6]*b.data[11] + a.data[7]*b.data[15];

    m->data[8] = a.data[8]*b.data[0] + a.data[9]*b.data[4] + a.data[10]*b.data[8] + a.data[11]*b.data[12];
    m->data[9] = a.data[8]*b.data[1] + a.data[9]*b.data[5] + a.data[10]*b.data[9] + a.data[11]*b.data[13];
    m->data[10] = a.data[8]*b.data[2] + a.data[9]*b.data[6] + a.data[10]*b.data[10] + a.data[11]*b.data[14];
    m->data[11] = a.data[8]*b.data[3] + a.data[9]*b.data[7] + a.data[10]*b.data[11] + a.data[11]*b.data[15];

    m->data[12] = a.data[12]*b.data[0] + a.data[13]*b.data[4] + a.data[14]*b.data[8] + a.data[15]*b.data[12];
    m->data[13] = a.data[12]*b.data[1] + a.data[13]*b.data[5] + a.data[14]*b.data[9] + a.data[15]*b.data[13];
    m->data[14] = a.data[12]*b.data[2] + a.data[13]*b.data[6] + a.data[14]*b.data[10] + a.data[15]*b.data[14];
    m->data[15] = a.data[12]*b.data[3] + a.data[13]*b.data[7] + a.data[14]*b.data[11] + a.data[15]*b.data[15];
}

// Transpose MMat4 using row-major order
LFINLINE MMat4 mmat4_row_translation(MMat4 a, Vec3 b)
{
    MMat4 *m = &a;
    m->data[12] += b.x; 
    m->data[13] += b.y; 
    m->data[14] += b.z; 
    return *m;
}

// Transpose MMat4 using column-major order
LFINLINE MMat4 mmat4_translate(MMat4 a, Vec3 b)
{
    // MMat4 m = mat4_identity();
    MMat4 *m = &a;
    m->data[3] += b.x; 
    m->data[7] += b.y; 
    m->data[11] += b.z; 
    return *m;
}

// Rotate MMat4 a by Vec3 b
LFINLINE MMat4 mmat4_rotate2D(MMat4 a, f32 degree)
{
    MMat4 *m = &a;
    f32 radians = degree * (M_PI / 180);
    
    m->data[0] = cos(degree);
    m->data[1] = sin(degree);
    m->data[4] = -sin(degree);
    m->data[5] = cos(degree);
    
    return *m;
}

// Scale MMat4 a by Vec3 b
LFINLINE MMat4 mmat4_scale(MMat4 a, Vec3 b)
{
    // MMat4 m = mat4_identity();
    MMat4 *m = &a;
    
    m->data[0] *= b.x;
    m->data[5] *= b.y;
    m->data[10] *= b.z;
    
    return *m;
}

LFINLINE MMat4 mmat4_perspective(f32 fov, f32 aspect_ratio, f32 near_plane, f32 far_plane)
{
    f32 rad = fov * LF_DEG2RAD;
    f32 zoom = tan(rad * 0.5f);

    f32 n = near_plane;
    f32 f = far_plane;

    MMat4 m = mmat4_identity();
    m.data[0] = 1.0f / (zoom * aspect_ratio);
    m.data[5] = 1.0f / zoom;
    m.data[10] = -((f+n) / (f-n));
    m.data[11] = -((2.0f*f*n) / (f-n));
    m.data[14] = -1.0f;
    m.data[15] = 0.0f;

    return m;
}

LFINLINE void mat4_print(Mat4 m)
{
    f32 c0[4] = {m.column[0][0], m.column[0][1], m.column[0][2], m.column[0][3]};
    f32 c1[4] = {m.column[1][0], m.column[1][1], m.column[1][2], m.column[1][3]};
    f32 c2[4] = {m.column[2][0], m.column[2][1], m.column[2][2], m.column[2][3]};
    f32 c3[4] = {m.column[3][0], m.column[3][1], m.column[3][2], m.column[3][3]};
    
    printf("(");
    for(int i = 0; i < 4; i++)
        printf("%.2f ", c0[i]);
    printf(")\n");

    printf("(");
    for(int i = 0; i < 4; i++)
        printf("%.2f ", c1[i]);
    printf(")\n");
        
    printf("(");
    for(int i = 0; i < 4; i++)
        printf("%.2f ", c2[i]);
    printf(")\n");

    printf("(");
    for(int i = 0; i < 4; i++)
        printf("%.2f ", c3[i]);
    printf(")\n");
}


#endif // MAT4_H