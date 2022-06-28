#pragma once

#include "colossus/core/defs.h"
#include "colossus/ecs/entity.h"

/*
 * An abstract structure containing all data neccessary for the ECS to function.
 */
typedef struct ECS ECS;
/*
 * A structure representing all the data a component usese.
 */
typedef struct {
   /* The size of the component type. */
    const U64 size;
    /* A contiguous chunk of data containing all component data. */
    void *storage;
    /* A dynamic array containing all entities which this component type is attached to. */
    Entity *entities;
} Component;
/*
 * A system function to be ran every ecsRun() call.
 */
typedef void (*System)(ECS *ecs);

/*
 * Create and configure an ECS.
 *
 * max_entity_count - Max amount of entities able to be active at once.
 * system_group_count - How many system groups there should be.
 * 
 * Returns the configured ECS.
 */
extern ECS *ecsCreate(U32 max_entity_count, U32 system_group_count);
/*
 * Destroy and clean up the ECS, freeing all used memory.
 * Sets the passed ECS pointer to NULL.
 *
 * ecs - A pointer to an ECS pointer.
 */
extern void ecsDestroy(ECS **ecs);
/*
 * Configures some internal state for the ECS when the user has added all components.
 *
 * ecs - Pointer to ECS.
 */
extern void ecsBake(ECS *ecs);

/*
 * Add a component to an ECS.
 * The component will get an ID starting from 0 and increasing with every component.
 * 
 * ecs - Poitner to ECS.
 * size - Size of the component type.
 * 
 * Returns component ID.
 */
extern U32 ecsAddComponent(ECS *ecs, U64 size);
/*
 * Retrieve a component.
 *
 * ecs - Poitner to ECS.
 * component_id - ID of component.
 * 
 * Return the component queried. Returns NULL if not found.
 */
extern const Component *ecsGetComponent(ECS *ecs, U32 component_id);

/*
 * Adds a system to a specified system group.
 * A system group is a collection of systems executed when its group is ran with ecsRun(ecs, group_id)
 * 
 * ecs - Pointer to ECS.
 * system_group_id - ID of system group.
 * system - System function.
 */
extern void ecsAddSystem(ECS *ecs, System system, U32 system_group_id);
/*
 * Run all systems within a system group.
 * Run only systems contained in the specified system group.
 * 
 * ecs - Pointer to ECS.
 * system_group_id - ID of system group.
 * 
 * Returns 0/false if the system group couldn't be found. Returns 1/true if it successfully ran the systems in the system group.
 */
extern I32 ecsRun(ECS *ecs, U32 system_group_id);

/*
 * Prints out the look up table for entities and components.
 *
 * ecs - Pointer to ECS.
 */
extern void ecsDebugPrintTable(ECS *ecs);
