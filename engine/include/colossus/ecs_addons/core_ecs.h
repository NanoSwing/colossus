#pragma once

#include "colossus/core/defs.h"
#include "colossus/ecs/ecs.h"
#include "colossus/core/math/vec2.h"

typedef struct {
    Vec2 position;
    F32 rotation;
    Vec2 scale;
} Transform;
extern I32 COMP_TRANSFORM;

extern void ecsAddonCore(ECS *ecs, U32 system_group);
