#pragma once

#include "colossus/core/math/vec4.h"

typedef struct {
    Vec4 a, b, c, d;
} Mat4;
#define mat4Identity mat4(vec4(1, 0, 0, 0), vec4(0, 1, 0, 0), vec4(0, 0, 1, 0), vec4(0, 0, 0, 1))

static inline Mat4 mat4(Vec4 a, Vec4 b, Vec4 c, Vec4 d) { return (Mat4) {a, b, c, d}; }
// Stolen from: http://learnwebgl.brown37.net/08_projections/projections_ortho.html
static inline Mat4 mat4OrthoProjection(F32 left, F32 right, F32 top, F32 bottom, F32 near, F32 far)
{
    Mat4 proj = mat4Identity;

    F32 mid_x = (left + right) / 2.0f;
    F32 mid_y = (bottom + top) / 2.0f;
    F32 mid_z = (-near + -far) / 2.0f;
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
