#include "colossus/ecs/entity.h"
#include "colossus/core/da.h"
#include "ecs/internal_ecs.h"
#include "colossus/core/utils.h"

#include <stdlib.h>
#include <string.h>

Entity ecsCreateEntity(ECS *ecs)
{
    return (Entity) {.ecs = ecs, internalEcsGetEntityID(ecs)};
}

Entity entityGetByID(ECS *ecs, U32 entity_id)
{
    return (Entity) {.ecs = ecs, .ID = entity_id};
}

void entityDestroy(Entity entity)
{
    for (U32 i = 0; i < daCount(entity.ecs->components); i++) {
        entityRemoveComponent(entity, i);
    }
}

void entityAddComponent(Entity entity, U32 component_id)
{
    const ECS *ecs = entity.ecs;
    ecs->entity_component_table[entity.ID + component_id * ecs->max_entity_count] = true;
    memset(ecs->components[component_id].storage + entity.ID * ecs->components[component_id].size, 0, ecs->components[component_id].size);
    daPush(ecs->components[component_id].entities, entity);
}

static I32 compEntity(const void *_a, const void *_b)
{
    const Entity *a = _a;
    const Entity *b = _b;

    return compInt(&a->ID, &b->ID);
}
void entityRemoveComponent(Entity entity, U32 component_id)
{
    const ECS *ecs = entity.ecs;
    Component comp = ecs->components[component_id];
    ecs->entity_component_table[entity.ID + component_id * ecs->max_entity_count] = false;
    qsort(comp.entities, daCount(comp.entities), sizeof(Entity), compEntity);
    I32 index = binarySearch(comp.entities, &entity, 0, daCount(comp.entities), sizeof(Entity), compEntity);
    if (index == -1) {
        return;
    }
    daPopAt(comp.entities, index, NULL);
}

B8 entityHasComponent(Entity entity, U32 component_id)
{
    return entity.ecs->entity_component_table[entity.ID + component_id * entity.ecs->max_entity_count];
}

void *entityGetComponent(Entity entity, U32 component_id)
{
    if (!entityHasComponent(entity, component_id)) {
        return NULL;
    }
    Component comp = entity.ecs->components[component_id];
    return comp.storage + entity.ID * comp.size;
}
