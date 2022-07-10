#pragma once

#include "colossus/core/defs.h"
#include "colossus/graphics/buffers/VAO.h"
#include "colossus/graphics/buffers/VBO.h"
#include "colossus/graphics/buffers/EBO.h"

/*
 * Batcher structure.
 */
typedef struct {
    /* Vertex array object. */
    VAO vao;
    /* Vertex buffer object. */
    VBO vbo;
    /* Element buffer object. */
    EBO ebo;

    /* Vertex buffer containing vertex data. */
    void *vertex_buffer;
    /* Current amount of vertices stored in vertex buffer. */
    I32 vertex_count;
    /* Size of a single vertex. */
    U64 vertex_size;
    /* Max amount of vertices able to be stored in vertex buffer. */
    I32 max_vertex_count;
} Batcher;

/*
 * Create a batcher. Used for rendering.
 *
 * vertex_size - Size of a vertex.
 * max_vertex_count - Max amount of vertices contained in buffers.
 * layout - Vertex layout for configuring buffers.
 * layout_count - Layout parameter count.
 * indices - Indices.
 * index_count - Amount of indices stored in indices argument.
 * 
 * Returns configured batcher.
 */
extern Batcher batcherCreate(U64 vertex_size, I32 max_vertex_count, const VertexLayout *layout, I32 layout_count, const I32 *indices, I32 index_count);
/*
 * Destroy a batcher. Destroying all buffers and memory used.
 *
 * batcher - Batcher.
 */
extern void batcherDestroy(Batcher *batcher);

/*
 * Executes a draw call with the currently bound shader and resets the vertex count.
 *
 * batcher - Batcher.
 */
extern void batcherFlush(Batcher *batcher);
