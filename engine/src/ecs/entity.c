#include "colossus/ecs/entity.h"
#include "colossus/core/da.h"
#include "ecs/internal_ecs.h"
#include "colossus/core/utils.h"
#include "colossus/core/logger.h"

#include <stdlib.h>
#include <string.h>

/*
 * Compare function for sorting and searching entities by ID.
 */
static I32 compEntity(const void *_a, const void *_b)
{
    const Entity *a = _a;
    const Entity *b = _b;

    return compInt(&a->id, &b->id);
}

static B8 checkNullEntity(Entity ent) { return (ent.id == NULL_ENTITY.id || ent.ecs == NULL_ENTITY.ecs); }

/*
 * Create an entity instance with a ID and the ECS.
 */
Entity ecsCreateEntity(ECS *ecs)
{
    return (Entity) {.ecs = ecs, internalEcsGetEntityID(ecs)};
}

/*
 * Remove all components from entity.
 */
void entityDestroy(Entity entity)
{
    if (checkNullEntity(entity)) {
        return;
    }

    for (I32 i = 0; i < daCount(entity.ecs->components); i++) {
        if (entityHasComponent(entity, i)) {
            entityRemoveComponent(entity, i);
        }
    }

    daPush(entity.ecs->available_entities, (I32) entity.id);
}

/*
 * Set the entity component lookup table to true.
 * Remove previous component data.
 * Add entity to component entities array.
 */
void entityAddComponent(Entity entity, I32 component_id)
{
    if (checkNullEntity(entity)) {
        return;
    }

    const ECS *ecs = entity.ecs;
    ecs->entity_component_table[entity.id + component_id * ecs->max_entity_count] = true;
    memset(ecs->components[component_id].storage + entity.id * ecs->components[component_id].size, 0, ecs->components[component_id].size);
    daPush(ecs->components[component_id].entities, entity);
}

/*
 * Remove true flag from entity component lookup table.
 * Sort the component entities array.
 * Search for the index of the entity within the component entities array.
 * Remove entity if found.
 */
void entityRemoveComponent(Entity entity, I32 component_id)
{
    if (checkNullEntity(entity)) {
        return;
    }

    const ECS *ecs = entity.ecs;
    Component comp = ecs->components[component_id];
    ecs->entity_component_table[entity.id + component_id * ecs->max_entity_count] = false;
    qsort(comp.entities, daCount(comp.entities), sizeof(Entity), compEntity);
    I32 index = binarySearch(comp.entities, &entity, 0, daCount(comp.entities), sizeof(Entity), compEntity);
    if (index == -1) {
        return;
    }
    daPopAt(comp.entities, index, NULL);
}

/*
 * Return entity component lookup table state.
 */
B8 entityHasComponent(Entity entity, I32 component_id)
{
    if (checkNullEntity(entity)) {
        return;
    }

    return entity.ecs->entity_component_table[entity.id + component_id * entity.ecs->max_entity_count];
}

/*
 * If the entity doesn't have the component, return NULL.
 * Else just return the component data.
 */
void *entityGetComponent(Entity entity, I32 component_id)
{
    if (checkNullEntity(entity)) {
        return;
    }
    
    if (!entityHasComponent(entity, component_id)) {
        return NULL;
    }
    Component comp = entity.ecs->components[component_id];
    return comp.storage + entity.id * comp.size;
}
