#include "ecs/internal_ecs.h"
#include "colossus/ecs/entity.h"
#include "colossus/core/da.h"
#include "colossus/core/logger.h"

#include <malloc.h>
#include <string.h>
#include <stdio.h>

/*
 * Initialize the ECS.
 */
ECS *ecsCreate(I32 max_entity_count, I32 system_group_count)
{
    ECS *ecs = malloc(sizeof(ECS));

    ecs->max_entity_count = max_entity_count;

    ecs->available_entities = daCreate(sizeof(I32));
    for (I32 i = 0; i < max_entity_count; i++) {
        daPush(ecs->available_entities, i);
    }

    ecs->components = daCreate(sizeof(Component));

    // Add system groups
    ecs->systems = daCreate(sizeof(System *));
    for (I32 i = 0; i < system_group_count; i++) {
        daPush(ecs->systems, daCreate(sizeof(System)));
    }

    return ecs;
}

/*
 * Clean up the ECS.
 */
void ecsDestroy(ECS **ecs)
{
    // Free all component data
    for (I32 i = 0; i < daCount((*ecs)->components); i++) {
        daDestroy((*ecs)->components[i].entities);
        free((*ecs)->components[i].storage);
    }
    daDestroy((*ecs)->components);
    
    free((*ecs)->entity_component_table);

    // Free all system groups
    for (I32 i = 0; i < daCount((*ecs)->systems); i++) {
        daDestroy((*ecs)->systems[i]);
    }
    daDestroy((*ecs)->systems);

    daDestroy((*ecs)->available_entities);

    free(*ecs);
    // Make sure the pointer doesn't presist.
    *ecs = NULL;
}

/*
 * Create the entity component lookup table.
 */
void ecsBake(ECS *ecs)
{
    ecs->entity_component_table = calloc(daCount(ecs->components), ecs->max_entity_count);
}

/*
 * Get component pointer in the components array by pusing NULL.
 * Set the read-only size of the component.
 * Setup the component.
 * 
 * Return component index.
 */
I32 ecsAddComponent(ECS *ecs, U64 size)
{
    Component comp = {
        .size = size,
    };

    comp.entities = daCreate(sizeof(Entity));
    comp.storage = malloc(size * ecs->max_entity_count);

    daPush(ecs->components, comp);
    return daCount(ecs->components) - 1;
}

/*
 * Return the component requested.
 */
const Component *ecsGetComponent(ECS *ecs, I32 component_id)
{
    // If the component ID is too high, return NULL
    if (component_id >= daCount(ecs->components)) {
        logWarn("Component ID too high.");
        return NULL;
    }

    return &ecs->components[component_id];
}

/*
 * Add the system to the system group.
 */
void ecsAddSystem(ECS *ecs, System system, I32 system_group_id)
{
    daPush(ecs->systems[system_group_id], system);
}

/*
 * Make sure the system group exists.
 *
 * Run all systems inside the system group.
 */
I32 ecsRun(ECS *ecs, I32 system_group_id)
{
    if (system_group_id >= daCount(ecs->systems)) {
        return false;
    }

    for (I32 i = 0; i < daCount(ecs->systems[system_group_id]); i++) {
        ecs->systems[system_group_id][i](ecs);
    }

    return true;
}

/*
 * Just return the next entity.
 * TODO: Update with deleted entities.
 */
I32 internalEcsGetEntityID(ECS *ecs)
{
    if (daCount(ecs->available_entities) == 0) {
        logWarn("Max amount of entities reached.");
        return -1;
    }

    I32 ent;
    daPop(ecs->available_entities, &ent);

    return ent;
}

/*
 * Print the 2D entity component lookup table array.
 */
void ecsDebugPrintTable(ECS *ecs)
{
    for (I32 y = 0; y < daCount(ecs->components); y++) {
        for (I32 x = 0; x < ecs->max_entity_count; x++) {
            printf("%d ", ecs->entity_component_table[x + y * ecs->max_entity_count]);
        }
        printf("\n");
    }
}
