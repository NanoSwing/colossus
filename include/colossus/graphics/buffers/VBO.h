#pragma once

#include "colossus/core/defs.h"

/*
 * Vertex buffer object.
 */
typedef struct {
    /* ID. */
    I32 id;
    /* Size of a vertex. */
    U64 vertex_size;
    /* Is data dynamic or static. */
    B8 dynamic;
} VBO;

/*
 * Create a dynamic vertex buffer object.
 *
 * vertex_size - Size of a vertex.
 * vertex_count - Max amount of vertices in the vertex buffer.
 * 
 * Returns vertex buffer object.
 */
extern VBO vboCreateDynamic(U64 vertex_size, I32 vertex_count);
/*
 * Create a static vertex buffer object.
 *
 * vertex_size - Size of a vertex.
 * vertex_count - Max amount of vertices in the vertex buffer.
 * vertices - Vertex data to be stored in buffer.
 * 
 * Returns vertex buffer object.
 */
extern VBO vboCreateStatic(U64 vertex_size, I32 vertex_count, const void *vertices);
/*
 * Destroy vertex buffer object.
 *
 * vbo - Vertex buffer object.
 */
extern void vboDestroy(VBO vbo);

/*
 * Update vertex data in a dynamic vertex buffer object.
 *
 * vbo - Vertex buffer object.
 * data - Vertex data.
 * data_size - Size of data.
 */
extern void vboSendData(VBO vbo, const void *data, U64 data_size);
/*
 * Bind / used vertex buffer object.
 *
 * vbo - Vertex buffer object.
 */
extern void vboBind(VBO vbo);
/*
 * Unbind / stop using any buffer object.
 */
extern void vboUnbind(void);
