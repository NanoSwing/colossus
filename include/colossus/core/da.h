#pragma once

#include "colossus/core/defs.h"

/*
 * Create a dynamic array.
 *
 * size - Size of the data type of the dynamic array.
 */
extern void *daCreate(U64 size);
extern void _daDestroy(void **da);
extern void *_daPushAt(void **da, I32 index, void *data);
extern void _daPopAt(void **da, I32 index, void *output);
/*
 * Get the amount of items stored in a dynamic array.
 *
 * da - Dynamic array.
 * 
 * Returns the amount of items stored.
 */
extern I64 daCount(const void *da);

/*
 * Frees all allocated memory dedicated to the dynamic array and sets the dynamic array pointer to null.
 */
#define daDestroy(da) _daDestroy((void **) &da)

/*
 * Inserts data at the specified index in the dynamic array.
 *
 * da - Dynamic array.
 * index - Index.
 * data - The data to be inserted.
 * 
 * Returns the pushed item.
 */
#define daPushAt(da, index, data) ({\
        void *__da_output; \
        typeof(data) __da_temp_data = data; \
        __da_output = _daPushAt((void **) &da, index, &__da_temp_data);\
        __da_output; \
    })
/*
 * Inserts data at the end of the dynamic array.
 *
 * da - Dynamic array.
 * data - Data to be inserted.
 * 
 * Returns the pushed item. 
 */
#define daPush(da, data) daPushAt(da, daCount(da), data)

/*
 * Inserts data at the specified index in the dynamic array.
 *
 * da - Dynamic array.
 * index - Index.
 * output - Copies the data at the index to this argument if not NULL.
 */
#define daPopAt(da, index, output) _daPopAt((void **) &da, index, output);
/*
 * Inserts data at the specified index in the dynamic array.
 *
 * da - Dynamic array.
 * output - Copies the data at the index to this argument if not NULL.
 */
#define daPop(da, output) _daPopAt((void **) &da, daCount(da) - 1, output);
