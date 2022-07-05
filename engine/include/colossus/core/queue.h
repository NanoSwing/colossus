#pragma once

#include "colossus/core/defs.h"

/*
 * A structure containing a list of elements.
 */
typedef struct Queue Queue;

/*
 * Creates a queue.
 *
 * filler - List copied into the queue.
 * amount - Element count in list.
 * size - Size of element type.
 * 
 * Returns the queue.
 */
extern Queue *queueCreate(void *filler, I32 amount, U64 size);
/*
 * Destroy the queue, freeing used memory.
 *
 * queue - Pointer to a queue pointer which will be set to NULL.
 */
extern void queueDestroy(Queue **queue);

/*
 * Retrieves the first element in the queue, pushing it to the end.
 *
 * queue - Queue.
 * output - Pointer to address where output will be copied to.
 */
extern void queueGet(const Queue *queue, void *output);
