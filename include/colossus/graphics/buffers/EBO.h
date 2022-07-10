#pragma once

#include "colossus/core/defs.h"

/*
 * Element buffer object.
 */
typedef struct {
    /* ID. */
    I32 id;
} EBO;

/*
 * Create an elmenet buffer object.
 *
 * indices - Indices to be bound into buffer.
 * index_count - Amount of indices passed in.
 * 
 * Returns created element buffer object.
 */
extern EBO eboCreate(const I32 *indices, I32 index_count);
/*
 * Destroy element buffer object.
 *
 * ebo - Element buffer object.
 */
extern void eboDestroy(EBO ebo);

/*
 * Bind / use element buffer object.
 * 
 * ebo - Element buffer object.
 */
extern void eboBind(EBO ebo);
/*
 * Unbind / stop using any element buffer object.
 */
extern void eboUnbind(void);
