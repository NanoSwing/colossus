#pragma once

#include "colossus/core/defs.h"
#include "colossus/ecs/ecs.h"

typedef struct {
    F32 delta_time;
    F32 fixed_delta_time;
} GlobalState;
extern GlobalState global;

typedef struct Engine Engine;

typedef enum {
    SYS_FIXED_UPDATE,
    SYS_PRE_UPDATE,
    SYS_UPDATE,
    SYS_LATE_UPDATE,

    SYS_GROUP_COUNT
} SystemGroup;

extern Engine *engineCreate(I32 width, I32 height, const char *title, B8 resizable, I32 max_entity_count, ECS **ecs);
extern void engineSetup(Engine *engine);
extern void engineStart(Engine *engine);
extern void engineDestroy(Engine **engine);
