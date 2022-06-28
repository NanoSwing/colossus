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

static Resource *getResource(const char *name)
{
    Resource key;
    strcpy(key.name, name);
    Resource *resource = bsearch(&key, resources, daCount(resources), sizeof(Resource), compResource);

    return resource;
}

void resourceManagerInit(void)
{
    resources = daCreate(sizeof(Resource));
}

void _resourceAdd(const void *value, U64 size, const char *name)
{
    // No duplicate names
    if (getResource(name) != NULL) {
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

void _resourceUpdate(const void *value, const char *name)
{
    Resource *res = getResource(name);
    if (res == NULL) {
        return;
    }

    memcpy(res->value, value, res->size);
}

void *resourceGet(const char *name)
{
    Resource *resource = getResource(name);
    if (resource == NULL) {
        return NULL;
    }

    return resource->value;
}

void resourceDelete(const char *name)
{
    Resource key;
    strcpy(key.name, name);
    I32 index = binarySearch(&key, resources, 0, daCount(resources), sizeof(Resource), compResource);

    if (index == -1) {
        return;
    }

    daPopAt(resources, index, NULL);
}

void resourceManagerTerminate(void)
{
    for (U32 i = 0; i < daCount(resources); i++) {
        free(resources[i].value);
    }
    daDestroy(resources);
}
