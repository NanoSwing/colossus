#pragma once

#include "colossus/core/defs.h"
#include "graphics/shader.h"
#include "colossus/core/math/mat4.h"

typedef struct {
    U32 size;
    U64 offset;
} Layout;

typedef struct {
    U32 vertex_buffer;
    U32 element_array;
    U32 vertex_array;

    Shader shader;
    Mat4 *projection;
    U32 textures[32];
    U32 texture_count;

    U32 max_quads;

    U64 vertex_size;

    // Array
    void *quad_buffer;
    void *quad_pointer;
    U32 quad_count;
} Batcher;

extern Batcher createBatcher(U32 max_quads, U64 vertex_size, const Layout *layout, Mat4 *projection, Shader shader);
extern void destroyBatcher(Batcher batcher);

extern void flushBatcher(Batcher *batcher);
extern void startBatcher(Batcher *batcher);
extern void endBatcher(Batcher *batcher);
