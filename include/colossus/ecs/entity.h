#pragma once

#include "colossus/core/defs.h"

/*
 * A entity which equals the NULL keyword.
 * Used when passing an entity to a function without knowing if retrieving the entity was succesful.
 */
#define NULL_ENTITY (Entity) {.ecs = NULL, .id = -1}

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
    const I32 id;
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
extern void _entityAddComponent(Entity entity, I32 component_id, const void *config);
#define entityAddComponent(entity, component_id, config) ({ \
    __typeof(config) __temp_config = config; \
    _entityAddComponent(entity, component_id, &__temp_config); \
})
/*
 * Remove a component from an entity.
 *
 * entity - Entity.
 * component_id - ID of component.
 */
extern void entityRemoveComponent(Entity entity, I32 component_id);
/*
 * Check if an entity has a component.
 *
 * entity - Entity.
 * component_id - ID of component.
 * 
 * Returns 1/true if entity has the component, returns 0/false if not.
 */
extern B8 entityHasComponent(Entity entity, I32 component_id);
/*
 * Get the component data for an entity.
 *
 * entity - Entity.
 * component_id - ID of component.
 * 
 * Returns the component data if entity has the component, return NULL if not.
 */
extern void *entityGetComponent(Entity entity, I32 component_id);
