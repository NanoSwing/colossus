#include "colossus/core/queue.h"
#include "colossus/core/logger.h"

#include <malloc.h>
#include <string.h>

struct Queue {
    U64 size;
    I32 amount;
    void *array;
};

Queue *queueCreate(void *filler, I32 amount, U64 size)
{
    Queue *queue = malloc(sizeof(Queue));

    queue->amount = amount;
    queue->size = size;
    queue->array = malloc(amount * size);
    memcpy(queue->array, filler, amount * size);

    return queue;
}

void queueDestroy(Queue **queue)
{
    free((*queue)->array);
    free(*queue);

    *queue = NULL;
}

void queueGet(const Queue *queue, void *output)
{
    if (output == NULL) {
        logWarn("Queue get, output can't be NULL.");
        return;
    }
    // Copy first element to output
    memcpy(output, queue->array, queue->size);
    // Move entire array one step to the left
    memcpy(queue->array, queue->array + queue->size, (queue->amount - 1) * queue->size);
    // Place first element at the end of the array
    memcpy(queue->array + (queue->amount - 1) * queue->size, output, queue->size);
}
