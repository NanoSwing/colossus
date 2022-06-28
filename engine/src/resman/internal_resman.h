#pragma once

#include "colossus/resman/resman.h"

typedef struct {
    void *value;
    char name[32];
    U64 size;
} Resource;
extern Resource *resources;
