#pragma once

#include "colossus/core/defs.h"
#include "colossus/core/utils.h"

#include <math.h>

typedef struct {
    F32 x, y, z;
} Vec3;

static inline Vec3 vec3(F32 x, F32 y, F32 z) { return (Vec3) {x, y, z}; }
static inline Vec3 vec3s(F32 scaler)  { return (Vec3) {scaler, scaler, scaler}; }

static inline Vec3 vec3Mul(Vec3 a, Vec3 b) { return vec3(a.x * b.x, a.y * b.y, a.z * b.z); }
static inline Vec3 vec3Div(Vec3 a, Vec3 b) { return vec3(a.x / b.x, a.y / b.y, a.z / b.z); }
static inline Vec3 vec3Add(Vec3 a, Vec3 b) { return vec3(a.x + b.x, a.y + b.y, a.z + b.z); }
static inline Vec3 vec3Sub(Vec3 a, Vec3 b) { return vec3(a.x - b.x, a.y - b.y, a.z - b.z); }

static inline Vec3 vec3MulS(Vec3 a, F32 scaler) { return vec3(a.x * scaler, a.y * scaler, a.z * scaler); }
static inline Vec3 vec3DivS(Vec3 a, F32 scaler) { return vec3(a.x / scaler, a.y / scaler, a.z / scaler); }
static inline Vec3 vec3AddS(Vec3 a, F32 scaler) { return vec3(a.x + scaler, a.y + scaler, a.z + scaler); }
static inline Vec3 vec3SubS(Vec3 a, F32 scaler) { return vec3(a.x - scaler, a.y - scaler, a.z - scaler); }

static inline F32 vec3Mag(Vec3 a) { return sqrt(pow(a.x, 2) + pow(a.y, 2) + pow(a.z, 2)); }
static inline Vec3 vec3Normalize(Vec3 a) { return vec3DivS(a, vec3Mag(a)); }

#define vec3Args(vec) vec.x, vec.y, vec.z
