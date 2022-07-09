#pragma once

#include "colossus/core/defs.h"
#include "colossus/graphics/buffers/VAO.h"
#include "colossus/graphics/buffers/VBO.h"
#include "colossus/graphics/buffers/EBO.h"

typedef struct {
    VAO vao;
    VBO vbo;
    EBO ebo;

    void *vertex_buffer;
    I32 vertex_count;
    U64 vertex_size;
    I32 max_vertex_count;
} Batcher;

extern Batcher batcherCreate(U64 vertex_size, I32 max_vertex_count, const VertexLayout *layoyt, I32 layout_count, const I32 *indices, I32 index_count);
extern void batcherDestroy(Batcher *batcher);

extern void batcherStart(Batcher *batcher);
extern void batcherStop(Batcher *batcher);
extern void batcherFlush(Batcher *batcher);
