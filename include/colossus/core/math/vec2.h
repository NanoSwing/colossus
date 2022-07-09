#pragma once

#include "colossus/core/defs.h"
#include "colossus/core/utils.h"

#include <math.h>

typedef struct {
    F32 x, y;
} Vec2;

static inline Vec2 vec2(F32 x, F32 y) { return (Vec2) {x, y}; }
static inline Vec2 vec2s(F32 scaler)  { return (Vec2) {scaler, scaler}; }

static inline Vec2 vec2Mul(Vec2 a, Vec2 b) { return vec2(a.x * b.x, a.y * b.y); }
static inline Vec2 vec2Div(Vec2 a, Vec2 b) { return vec2(a.x / b.x, a.y / b.y); }
static inline Vec2 vec2Add(Vec2 a, Vec2 b) { return vec2(a.x + b.x, a.y + b.y); }
static inline Vec2 vec2Sub(Vec2 a, Vec2 b) { return vec2(a.x - b.x, a.y - b.y); }

static inline Vec2 vec2MulS(Vec2 a, F32 scaler) { return vec2(a.x * scaler, a.y * scaler); }
static inline Vec2 vec2DivS(Vec2 a, F32 scaler) { return vec2(a.x / scaler, a.y / scaler); }
static inline Vec2 vec2AddS(Vec2 a, F32 scaler) { return vec2(a.x + scaler, a.y + scaler); }
static inline Vec2 vec2SubS(Vec2 a, F32 scaler) { return vec2(a.x - scaler, a.y - scaler); }

static inline F32 vec2Mag(Vec2 a) { return sqrt(a.x * a.x + a.y * a.y); }
static inline Vec2 vec2Normalize(Vec2 a) { return vec2MulS(a, 1.0f / vec2Mag(a)); }

/*
 * Rotates a vector clockwise.
 *
 * a - Vector.
 * degrees - Angle.
 * 
 * Returns a vector rotated by degrees.
 */
static inline Vec2 vec2Rot(Vec2 a, F32 degrees)
{
    if (degrees == 0) {
        return a;
    }

    F32 rads = rad(-degrees);
    return vec2(
        cos(rads) * a.x - sin(rads) * a.y,
        sin(rads) * a.x + cos(rads) * a.y
    );
}

#define vec2Args(vec) vec.x, vec.y
