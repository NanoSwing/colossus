#pragma once

#include "colossus/core/defs.h"
#include "colossus/ecs/entity.h"

typedef struct ECS ECS;
typedef struct {
    const U64 size;
    void *storage;
    Entity *entities; // Dynamic array
} Component;
typedef void (*System)(ECS *ecs);

extern ECS *ecsCreate(U32 max_entity_count, U32 system_group_count);
extern void ecsDestroy(ECS **ecs);
extern void ecsBake(ECS *ecs);

extern void ecsAddComponent(ECS *ecs, U64 size);
extern const Component *ecsGetComponent(ECS *ecs, U32 component_id);

extern void ecsAddSystem(ECS *ecs, U32 system_group_id, System system);
extern I32 ecsRun(ECS *ecs, U32 system_group_id);

extern void ecsDebugPrintTable(ECS *ecs);
