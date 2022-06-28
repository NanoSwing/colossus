#include "resman/internal_resman.h"
#include "colossus/core/da.h"
#include "colossus/core/utils.h"

#include <string.h>
#include <malloc.h>
#include <stdlib.h>

Resource *resources = NULL;

static I32 compResource(const void *_a, const void *_b)
{
    const Resource *a = _a;
    const Resource *b = _b;

    return strcmp(a->name, b->name);
}

static Resource *internalGetResource(const char *name)
{
    Resource key;
    strcpy(key.name, name);
    Resource *resource = bsearch(&key, resources, daCount(resources), sizeof(Resource), compResource);

    return resource;
}

static void resourceUpdate(const void *value, const char *name)
{
    Resource *res = internalGetResource(name);
    if (res == NULL) {
        return;
    }
    
    memcpy(res->value, value, res->size);
}

void resourceManagerInit(void)
{
    resources = daCreate(sizeof(Resource));
}

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

void *resourceGet(const char *name)
{
    Resource *resource = internalGetResource(name);
    if (resource == NULL) {
        return NULL;
    }

    return resource->value;
}

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

void resourceManagerTerminate(void)
{
    for (U32 i = 0; i < daCount(resources); i++) {
        free(resources[i].value);
    }
    daDestroy(resources);
}
