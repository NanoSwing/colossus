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
ECS *ecsCreate(U32 max_entity_count, U32 system_group_count)
{
    ECS *ecs = malloc(sizeof(ECS));

    ecs->max_entity_count = max_entity_count;
    ecs->current_entity_id = 0;

    ecs->components = daCreate(sizeof(Component));

    // Add system groups
    ecs->systems = daCreate(sizeof(System *));
    for (U32 i = 0; i < system_group_count; i++) {
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
    for (U32 i = 0; i < daCount((*ecs)->components); i++) {
        daDestroy((*ecs)->components[i].entities);
        free((*ecs)->components[i].storage);
    }
    daDestroy((*ecs)->components);
    
    free((*ecs)->entity_component_table);

    // Free all system groups
    for (U32 i = 0; i < daCount((*ecs)->systems); i++) {
        daDestroy((*ecs)->systems[i]);
    }
    daDestroy((*ecs)->systems);

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
U32 ecsAddComponent(ECS *ecs, U64 size)
{
    Component *comp = daPush(ecs->components, NULL);

    memcpy((U64 *) &comp->size, &size, sizeof(U64));
    
    comp->entities = daCreate(sizeof(Entity));
    comp->storage = malloc(size * ecs->max_entity_count);

    return daCount(ecs->components) - 1;
}

/*
 * Return the component requested.
 */
const Component *ecsGetComponent(ECS *ecs, U32 component_id)
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
void ecsAddSystem(ECS *ecs, System system, U32 system_group_id)
{
    daPush(ecs->systems[system_group_id], system);
}

/*
 * Make sure the system group exists.
 *
 * Run all systems inside the system group.
 */
I32 ecsRun(ECS *ecs, U32 system_group_id)
{
    if (system_group_id >= daCount(ecs->systems)) {
        return false;
    }

    for (U32 i = 0; i < daCount(ecs->systems[system_group_id]); i++) {
        ecs->systems[system_group_id][i](ecs);
    }

    return true;
}

/*
 * Just return the next entity.
 * TODO: Update with deleted entities.
 */
U32 internalEcsGetEntityID(ECS *ecs)
{
    return ecs->current_entity_id++;
}

/*
 * Print the 2D entity component lookup table array.
 */
void ecsDebugPrintTable(ECS *ecs)
{
    for (U32 y = 0; y < daCount(ecs->components); y++) {
        for (U32 x = 0; x < ecs->max_entity_count; x++) {
            printf("%d ", ecs->entity_component_table[x + y * ecs->max_entity_count]);
        }
        printf("\n");
    }
}
