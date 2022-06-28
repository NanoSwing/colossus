#include "resman/internal_resman.h"
#include "colossus/core/da.h"
#include "colossus/core/utils.h"

#include <string.h>
#include <malloc.h>
#include <stdlib.h>

/*
 * Define global resources.
 */
Resource *resources = NULL;

/*
 * Local function for comparing resources.
 * Used when sorting and searching.
 */
static I32 compResource(const void *_a, const void *_b)
{
    const Resource *a = _a;
    const Resource *b = _b;

    return strcmp(a->name, b->name);
}

/*
 * Local function to search for a resource.
 * 
 * Returns NULL if it wasn't found.
 */
static Resource *internalGetResource(const char *name)
{
    Resource key;
    strcpy(key.name, name);
    Resource *resource = bsearch(&key, resources, daCount(resources), sizeof(Resource), compResource);

    return resource;
}

/*
 * Local function to update a resource.
 * Used by _resourceSet.
 */
static void resourceUpdate(const void *value, const char *name)
{
    Resource *res = internalGetResource(name);
    if (res == NULL) {
        return;
    }
    
    memcpy(res->value, value, res->size);
}

/*
 * Create the resources array.
 */
void resourceManagerInit(void)
{
    resources = daCreate(sizeof(Resource));
}

/*
 * Update resource if it exists. Create a new resource if it doesn't.
 */
void _resourceSet(const char *name, const void *value, U64 size)
{
    // Update instead of creating new resource
    if (internalGetResource(name) != NULL) {
        resourceUpdate(value, name);
        return;
    }

    Resource res;
    res.value = malloc(size);
    memcpy(res.value, value, size);
    strcpy(res.name, name);
    res.size = size;

    daPush(resources, res);
    qsort(resources, daCount(resources), sizeof(Resource), compResource);
}

/*
 * Return the resource value if exists. Returns NULL if not.
 */
void *resourceGet(const char *name)
{
    Resource *resource = internalGetResource(name);
    if (resource == NULL) {
        return NULL;
    }

    return resource->value;
}

/*
 * Find a resource.
 * Don't do anything if it doesn't exist.
 * Delete it if it does.
 */
void resourceDelete(const char *name)
{
    Resource key;
    strcpy(key.name, name);
    I32 index = binarySearch(resources, &key, 0, daCount(resources), sizeof(Resource), compResource);

    if (index == -1) {
        return;
    }

    free(resources[index - 1].value);
    daPopAt(resources, index - 1, NULL);
}

/*
 * Free all used resource memory.
 * Free resources array.
 */
void resourceManagerTerminate(void)
{
    for (U32 i = 0; i < daCount(resources); i++) {
        free(resources[i].value);
    }
    daDestroy(resources);
}
