#pragma once

#include "colossus/core/defs.h"

typedef struct Queue Queue;

extern Queue *queueCreate(void *filler, I32 amount, U64 size);
extern void queueDestroy(Queue **queue);

extern void queueGet(const Queue *queue, void *output);
