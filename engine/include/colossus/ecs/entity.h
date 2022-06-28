#pragma once

#include "colossus/core/defs.h"

/*
 * Forward declare ECS to use within entities.
 */
typedef struct ECS ECS;
/*
 * A structure containing the definition of an entity.
 */
typedef struct {
    /* The ECS the entity belongs to. */
    const ECS *ecs;
    /* The ID of the entity. */
    const U32 ID;
} Entity;

/*
 * Get a new entity from the ECS.
 *
 * ecs - Pointer to ECS.
 * 
 * Returns the created entity.
 */
extern Entity ecsCreateEntity(ECS *ecs);
/*
 * Destroy the entity.
 * Removes all the components from the entity and making it available to be used again with ecsCreateEntity.
 * 
 * entity - Entity.
 */
extern void entityDestroy(Entity entity);

/*
 * Add a component to an entity.
 *
 * entity - Entity.
 * component_id - ID of component.
 */
extern void entityAddComponent(Entity entity, U32 component_id);
/*
 * Remove a component from an entity.
 *
 * entity - Entity.
 * component_id - ID of component.
 */
extern void entityRemoveComponent(Entity entity, U32 component_id);
/*
 * Check if an entity has a component.
 *
 * entity - Entity.
 * component_id - ID of component.
 * 
 * Returns 1/true if entity has the component, returns 0/false if not.
 */
extern B8 entityHasComponent(Entity entity, U32 component_id);
/*
 * Get the component data for an entity.
 *
 * entity - Entity.
 * component_id - ID of component.
 * 
 * Returns the component data if entity has the component, return NULL if not.
 */
extern void *entityGetComponent(Entity entity, U32 component_id);
