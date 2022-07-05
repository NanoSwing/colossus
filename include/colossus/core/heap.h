#pragma once

#include "colossus/core/defs.h"

/*
 * Structure containing a list of available data and used data.
 */
typedef struct Heap Heap;

/*
 * Creates a heap structure.
 *
 * size - Size of data type.
 * count - Amount of elements stored.
 * filler - Array containing the data to fill the available data list with.
 * reuse - Should the first object gotten be reused when heap is empty.
 * 
 * Returns the created heap.
 */
extern Heap *heapCreate(U64 size, I32 count, void *filler, B8 resue);
/*
 * Retrieves an element from the heap.
 *
 * heap - Heap.
 * output - Pointer to copy the output data to. If none are a vailable and the reuse flag is turned on for the heap then it returns the oldest element.
 */
extern void heapGet(Heap *heap, void *output);
/*
 * Puts some data back into the heap.
 *
 * heap - Heap.
 * data - Data.
 */
extern void heapRelease(Heap *heap, void *data);
/*
 * Destroy the heap, freeing the memory used.
 *
 * heap - Pointer to a heap address, which will be set to NULL.
 */
extern void heapDestroy(Heap **heap);
