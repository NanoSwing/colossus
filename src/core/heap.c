#include "colossus/core/heap.h"
#include "colossus/core/da.h"
#include "colossus/core/logger.h"

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

struct Heap {
    void *available;
    void *used;
    U64 size;
    B8 reuse;
};

Heap *heapCreate(U64 size, I32 count, void *filler, B8 resue)
{
    Heap *heap = malloc(sizeof(Heap));
    heap->size = size;
    heap->reuse = resue;
    heap->available = daCreate(size);
    for (I32 i = 0; i < count; i++) {
        _daPushAt(&heap->available, daCount(heap->available), filler + i * size);
    }
    heap->used = daCreate(size);

    return heap;
}

void heapGet(Heap *heap, void *output)
{
    if (daCount(heap->available) == 0) {
        if (heap->reuse) {
            daPopAt(heap->used, 0, output);
        } else {
            logWarn("Heap is empty.");
            return;
        }
    } else {
        daPopAt(heap->available, 0, output);
    }
    _daPushAt(&heap->used, daCount(heap->used), output);
}

void heapRelease(Heap *heap, void *data)
{
    for (I32 i = 0; i < daCount(heap->used); i++) {
        if (memcmp(heap->used + i * heap->size, data, heap->size) == 0) {
            daPopAt(heap->used, i, NULL);
            _daPushAt(&heap->available, daCount(heap->available), data);
        }
    }
}

void heapDestroy(Heap **heap)
{
    daDestroy((*heap)->available);
    daDestroy((*heap)->used);
    free(*heap);
    *heap = NULL;
}
