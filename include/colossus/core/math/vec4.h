#pragma once

#include "colossus/core/defs.h"
#include "colossus/core/utils.h"

#include <math.h>

typedef struct {
    F32 x, y, z, w;
} Vec4;

static inline Vec4 vec4(F32 x, F32 y, F32 z, F32 w) { return (Vec4) {x, y, z, w}; }
static inline Vec4 vec4s(F32 scaler)  { return (Vec4) {scaler, scaler, scaler, scaler}; }

static inline Vec4 vec4Mul(Vec4 a, Vec4 b) { return vec4(a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w); }
static inline Vec4 vec4Div(Vec4 a, Vec4 b) { return vec4(a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w); }
static inline Vec4 vec4Add(Vec4 a, Vec4 b) { return vec4(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w); }
static inline Vec4 vec4Sub(Vec4 a, Vec4 b) { return vec4(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w); }

static inline Vec4 vec4MulS(Vec4 a, F32 scaler) { return vec4(a.x * scaler, a.y * scaler, a.z * scaler, a.w * scaler); }
static inline Vec4 vec4DivS(Vec4 a, F32 scaler) { return vec4(a.x / scaler, a.y / scaler, a.z / scaler, a.w / scaler); }
static inline Vec4 vec4AddS(Vec4 a, F32 scaler) { return vec4(a.x + scaler, a.y + scaler, a.z + scaler, a.w + scaler); }
static inline Vec4 vec4SubS(Vec4 a, F32 scaler) { return vec4(a.x - scaler, a.y - scaler, a.z - scaler, a.w - scaler); }

static inline F32 vec4Mag(Vec4 a) { return sqrt(pow(a.x, 2) + pow(a.y, 2) + pow(a.z, 2) + pow(a.w, 2)); }
static inline Vec4 vec4Normalize(Vec4 a) { return vec4MulS(a, 1.0f / vec4Mag(a)); }

#define vec4Args(vec) vec.x, vec.y, vec.z, vec.w
