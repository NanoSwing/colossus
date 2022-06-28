#pragma once

#include "colossus/core/defs.h"

/*
 * Initializes the resource manager.
 */
extern void resourceManagerInit(void);

/*
 * Adds or updates a component depending if it exists.
 *
 * name - Name of resource.
 * value - Value.
 * size - Size of the resource type.
 */
extern void _resourceSet(const char *name, const void *value, U64 size);
/*
 * Retrieve the resource.
 *
 * name - Name of resource.
 * 
 * Returns NULL if resource wasn't found, otherwise returns resource data.
 */
extern void *resourceGet(const char *name);
/*
 * Delete a resource.
 *
 * name - Name of resource.
 */
extern void resourceDelete(const char *name);

/*
 * Clean up the resource manager. Freeing all used memory.
 */
extern void resourceManagerTerminate(void);

/*
 * Adds or updates a component depending if it exists.
 *
 * name - Name of resource.
 * value - Value to be set.
 */
#define resourceSet(name, value) { \
    typeof(value) __resource_temp_value = value; \
    _resourceSet(name, &__resource_temp_value, sizeof(__resource_temp_value)); \
}
