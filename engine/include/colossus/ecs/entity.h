#pragma once

#include "colossus/core/defs.h"

typedef struct ECS ECS;
typedef struct {
    const ECS *ecs;
    const U32 ID;
} Entity;

extern Entity ecsCreateEntity(ECS *ecs);
extern Entity entityGetByID(ECS *ecs, U32 entity_id);
extern void entityDestroy(Entity entity);

extern void entityAddComponent(Entity entity, U32 component_id);
extern void entityRemoveComponent(Entity entity, U32 component_id);
extern B8 entityHasComponent(Entity entity, U32 component_id);
extern void *entityGetComponent(Entity entity, U32 component_id);
