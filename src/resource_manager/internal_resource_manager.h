#pragma once

#include "colossus/resource_manager/resource_manager.h"

/*
 * Resource structure.
 */
typedef struct {
    /* Value stored in resource. */   
    void *value;
    /* Name of resource. */
    char name[32];
    /* Size of resoruce type. */
    U64 size;
} Resource;
/*
 * Global declaration of resources.
 */
extern Resource *resources;
