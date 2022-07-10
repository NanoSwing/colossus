#pragma once

#include "colossus/core/math/vec4.h"
#include "colossus/core/math/mat3.h"
#include "colossus/core/math/vec2.h"

#include <stdio.h>
#include <string.h>

/*
 * 4x4 matrix.
 */
typedef struct {
    Vec4 a, b, c, d;
} Mat4;

/*
 * A blank 4x4 matrix.
 */
#define mat4Identity mat4(vec4(1, 0, 0, 0), vec4(0, 1, 0, 0), vec4(0, 0, 1, 0), vec4(0, 0, 0, 1))

/*
 * Create a 4x4 matrix from vectors.
 *
 * a - First row.
 * b - Second row.
 * c - Third row.
 * d - Fourth row.
 * 
 * Returns the matrix.
 */
static inline Mat4 mat4(Vec4 a, Vec4 b, Vec4 c, Vec4 d) { return (Mat4) {a, b, c, d}; }

/*
 * Configures a 4x4 matrix into an orthographic projection.
 *
 * left - Left side of window.
 * right - Right side of window.
 * top - Top side of window.
 * bottom - Bottom side of window.
 * near - Near cutoff plane.
 * far - Far cutoff plane.
 * 
 * Returns an otrhographic projection.
 */
static inline Mat4 mat4OrthoProjection(F32 left, F32 right, F32 top, F32 bottom, F32 near, F32 far)
{
    // Stolen from: http://learnwebgl.brown37.net/08_projections/projections_ortho.html
    Mat4 proj = mat4Identity;

    F32 mid_x = (left + right) * 0.5f;
    F32 mid_y = (bottom + top) * 0.5f;
    F32 mid_z = (-near + -far) * 0.5f;
    proj.a.w = -mid_x;
    proj.b.w = -mid_y;
    proj.c.w = -mid_z;

    F32 scale_x = 2.0f / (right - left);
    F32 scale_y = 2.0f / (top - bottom);
    F32 scale_z = 2.0f / (far - near);
    proj.a.x = scale_x;
    proj.b.y = scale_y;
    proj.c.z = scale_z;

    return proj;
}

/*
 * Copy a 4x4 matrix into a float array.
 *
 * mat - 4x4 matrix to copy.
 * floats - Float array to copy into.
 */
static inline void mat4ToFloats(Mat4 mat, F32 floats[4][4]) { memcpy(floats, &mat, sizeof(Mat4)); }
/*
 * Copy a float array into a4x4 matrix.
 *
 * mat - 4x4 matrix to copy into.
 * floats - Float array to copy.
 */
static inline void mat4FromFloats(Mat4 *mat, F32 floats[4][4]) { memcpy(mat, floats, sizeof(Mat4)); }

/*
 * Invert a 4x4 matrix.
 *
 * mat - Matrix to invert.
 * 
 * Returns inverted matrix.
 */
static inline Mat4 mat4Inverse(Mat4 mat)
{
    // https://semath.info/src/inverse-cofactor-ex4.html

    // Create 3x3 matrix from an origin
    F32 m_f[4][4][3][3] = {0};
    F32 a_f[4][4];
    mat4ToFloats(mat, a_f);
    const Vec2 start_origin = vec2(2, 2);
    Vec2 origin = start_origin;

    for (I32 i = 0; i < 4; i++) {
        for (I32 j = 0; j < 4; j++) {
            origin.x = (I32) (start_origin.x + i) % 4;
            origin.y = (I32) (start_origin.y + j) % 4;
            for (I32 y = -1; y < 2; y++) {
                for (I32 x = -1; x < 2; x++) {
                    m_f[i][j][x + 1][y + 1] = a_f[(I32) (origin.x + x + 4) % 4][(I32) (origin.y + y + 4) % 4];
                }
            }
        }
    }

    F32 adj[4][4];
    for (I32 y = 0; y < 4; y++) {
        for (I32 x = 0; x < 4; x++) {
            Mat3 m;
            mat3FromFloat(&m, m_f[x][y]);
            adj[x][y] = mat3Determinant(m);
        }
    }

    F32 det = 0;
    det += mat.a.x * adj[0][0];
    det -= mat.b.x * adj[0][1];
    det += mat.c.x * adj[0][2];
    det -= mat.d.x * adj[0][3];

    I32 counter = 0;
    B8 neg = false;
    for (I32 y = 0; y < 4; y++) {
        for (I32 x = 0; x < 4; x++) {
            if (counter == 4) {
                counter = 0;
                neg = !neg;
            }
            if (neg) {
                adj[x][y] = -adj[x][y];
            }
            neg = !neg;
            counter++;
        }
    }

    for (I32 y = 0; y < 4; y++) {
        for (I32 x = 0; x < 4; x++) {
            adj[x][y] /= det;
        }
    }

    Mat4 ret;
    mat4FromFloats(&ret, adj);
    return ret;
}
