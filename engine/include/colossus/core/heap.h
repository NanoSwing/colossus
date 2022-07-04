#pragma once

#include "colossus/core/defs.h"

typedef struct Heap Heap;

extern Heap *heapCreate(U64 size, I32 count, void *filler);
extern void heapGet(Heap *heap, void *output);
extern void heapRelease(Heap *heap, void *data);
extern void heapDestroy(Heap **heap);
