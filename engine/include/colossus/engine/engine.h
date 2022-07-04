#pragma once

#include "colossus/graphics/graphics.h"
#include "colossus/ecs/ecs.h"

typedef struct {
    GraphicsConfig graphics_config;
    I32 max_entities;
} ColossusConfig;

typedef struct {
    F32 delta_time;
    F32 fixed_delta_time;
} ColossusGlobal;
extern ColossusGlobal global;

typedef enum {
    SYS_FIXED_UPDATE,
    SYS_PRE_UPDATE,
    SYS_UPDATE,
    SYS_LATE_UPDATE,

    SYS_COUNT
} SystemGroup;

extern void colossusInit(ColossusConfig config, ECS **ecs);
extern void colossusSetup(ECS *ecs);
extern void colossusStart(ECS *ecs);
extern void colossusTerminate(ECS **ecs);
