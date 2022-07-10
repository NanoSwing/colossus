#pragma once

#include "colossus/core/math/vec3.h"

typedef struct {
    Vec3 a, b, c;
} Mat3;

static inline F32 mat3Determinant(Mat3 mat)
{
    return mat.a.x*mat.b.y*mat.c.z + mat.b.x*mat.c.y*mat.a.z + mat.c.x*mat.a.y*mat.b.z - mat.c.x*mat.b.y*mat.a.z - mat.b.x*mat.a.y*mat.c.z - mat.a.x*mat.c.y*mat.b.z;
}

static inline Mat3 mat3FromFloat(F32 floats[3][3])
{
    return (Mat3) {
        {floats[0][0], floats[0][1], floats[0][2]},
        {floats[1][0], floats[1][1], floats[1][2]},
        {floats[2][0], floats[2][1], floats[2][2]}
    };
}
