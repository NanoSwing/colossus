#pragma once

#include "colossus/core/defs.h"

extern void resourceManagerInit(void);

extern void _resourceSet(const char *name, const void *value, U64 size);
extern void *resourceGet(const char *name);
extern void resourceDelete(const char *name);

extern void resourceManagerTerminate(void);

#define resourceSet(name, value) { \
    typeof(value) __resource_temp_value = value; \
    _resourceSet(name, &__resource_temp_value, sizeof(__resource_temp_value)); \
}
