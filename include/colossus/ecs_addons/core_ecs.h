#pragma once

#include "colossus/core/defs.h"
#include "colossus/ecs/ecs.h"
#include "colossus/core/math/vec2.h"

/*
 * Transform component.
 */
typedef struct {
    /* Position. */
    Vec2 position;
    /* Clockwise rotation in degrees. */
    F32 rotation;
    /* Scale. */
    Vec2 scale;
} Transform;
/* Component ID of the transform component. */
extern I32 COMP_TRANSFORM;

/*
 * Adds core components and systems used by all other addons.
 *
 * ecs - ECS.
 * system_group - System group to add core systems to.
 */
extern void ecsAddonCore(ECS *ecs, U32 system_group);
