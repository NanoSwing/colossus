#include "colossus/ecs/entity.h"
#include "colossus/core/da.h"
#include "ecs/internal_ecs.h"
#include "colossus/core/utils.h"

#include <stdlib.h>
#include <string.h>

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
    for (U32 i = 0; i < daCount(entity.ecs->components); i++) {
        entityRemoveComponent(entity, i);
    }
}

/*
 * Set the entity component lookup table to true.
 * Remove previous component data.
 * Add entity to component entities array.
 */
void entityAddComponent(Entity entity, U32 component_id)
{
    const ECS *ecs = entity.ecs;
    ecs->entity_component_table[entity.ID + component_id * ecs->max_entity_count] = true;
    memset(ecs->components[component_id].storage + entity.ID * ecs->components[component_id].size, 0, ecs->components[component_id].size);
    daPush(ecs->components[component_id].entities, entity);
}

/*
 * Compare function for sorting and searching entities by ID.
 */
static I32 compEntity(const void *_a, const void *_b)
{
    const Entity *a = _a;
    const Entity *b = _b;

    return compInt(&a->ID, &b->ID);
}
/*
 * Remove true flag from entity component lookup table.
 * Sort the component entities array.
 * Search for the index of the entity within the component entities array.
 * Remove entity if found.
 */
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

/*
 * Return entity component lookup table state.
 */
B8 entityHasComponent(Entity entity, U32 component_id)
{
    return entity.ecs->entity_component_table[entity.ID + component_id * entity.ecs->max_entity_count];
}

/*
 * If the entity doesn't have the component, return NULL.
 * Else just return the component data.
 */
void *entityGetComponent(Entity entity, U32 component_id)
{
    if (!entityHasComponent(entity, component_id)) {
        return NULL;
    }
    Component comp = entity.ecs->components[component_id];
    return comp.storage + entity.ID * comp.size;
}
