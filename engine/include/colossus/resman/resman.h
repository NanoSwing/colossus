#pragma once

#include "colossus/core/defs.h"

extern void resourceManagerInit(void);

extern void _resourceAdd(const void *value, U64 size, const char *name);
extern void _resourceUpdate(const void *value, const char *name);
extern void *resourceGet(const char *name);
extern void resourceDelete(const char *name);

extern void resourceManagerTerminate(void);

#define resourceAdd(value, name) { \
    typeof(value) __resource_temp_value = value; \
    _resourceAdd(&__resource_temp_value, sizeof(__resource_temp_value), name); \
}

#define resourceUpdate(value, name) { \
    typeof(value) __resource_temp_value = value; \
    _resourceUpdate(&__resource_temp_value, name); \
}
