#pragma once

#include "colossus/core/math/vec3.h"

#include <string.h>

/*
 * 3x3 Matrix
 */
typedef struct {
    Vec3 a, b, c;
} Mat3;

/*
 * Calculates the determinant of 3x3 vector.
 *
 * mat - Matrix.
 * 
 * Returns the determinant.
 */
static inline F32 mat3Determinant(Mat3 mat)
{
    return mat.a.x*mat.b.y*mat.c.z + mat.b.x*mat.c.y*mat.a.z + mat.c.x*mat.a.y*mat.b.z - mat.c.x*mat.b.y*mat.a.z - mat.b.x*mat.a.y*mat.c.z - mat.a.x*mat.c.y*mat.b.z;
}

/*
 * Copies a float array into a 3x3 matrix.
 *
 * mat - Matrix to copy into.
 * floats - Float array copy.
 */
static inline void mat3FromFloat(Mat3 *mat, F32 floats[3][3])
{
    memcpy(mat, floats, sizeof(Mat3));
}
