#pragma once

#include "colossus/core/defs.h"
#include "graphics/shader.h"
#include "colossus/core/math/mat4.h"
#include "colossus/graphics/texture.h"

/*
 * Structure for a shader layout.
 */
typedef struct {
    /* How many floats the parameter contains. */
    U32 size;
    /* How many bytes from the beginning of the struct does it recide. */
    U64 offset;
} Layout;

/*
 * Structure representing a batch renderer.
 */
typedef struct {
    /* OpenGL vertex buffer object. */
    U32 vertex_buffer;
    /* OpenGL element buffer object. */
    U32 element_buffer;
    /* OpenGL vertex array object */
    U32 vertex_array;

    /* Shader used to render. */
    Shader shader;
    /* Pointer to a projection matrix. */
    Mat4 *projection;
    /* Array of textures. */
    U32 textures[32];
    /* Keep track of textures loaded. */
    U32 texture_count;

    /* Max amount of quads before a flush happens. */
    U32 max_quads;

    /* Size of a vertex struct. */
    U64 vertex_size;

    /* Array of vertices. */
    void *quad_buffer;
    /* Pointer to quad_buffer. Used when calculating size of batch. */
    void *quad_pointer;
    /* Keep track of quads in current batch. */
    U32 quad_count;
} Batcher;

/*
 * Initialize a batch renderer.
 *
 * max_quads - Max amount of quads before a flush.
 * vertex_size - Size of vertex used.
 * layout - A dynamic array passed to define how the shader should handle the passed vertex data.
 * projection - Pointer to a projection matrix.
 * shader - Shader.
 * 
 * Returns the initialized batch renderer.
 */
extern Batcher batcherCreate(U32 max_quads, U64 vertex_size, const Layout *layout, Mat4 *projection, Shader shader);
/*
 * Frees all memeory used by the batcher and destroys the shader.
 */
extern void batcherDestroy(Batcher batcher);

/*
 * Binds all textures and makes an OpenGL draw call.
 *
 * batcher - Batch renderer.
 */
extern void batcherFlush(Batcher *batcher);
/*
 * Resets quad_pointer for a new batch.
 *
 * batcher - Batch renderer.
 */
extern void batcherStart(Batcher *batcher);
/*
 * Tells the batch renderer how big the batch is from how many bytes the quad_pointer has advenced in memory.
 *
 * batcher - Batch renderer.
 */
extern void batcherEnd(Batcher *batcher);
/*
 * Handels automatic flushing when texture cap or quad cap is reached.
 * Also handels texture adding. If texture_id or texture_index is null, no texture is added.
 * 
 * batcher - Batch renderer.
 * texture_id - OpenGL texture ID.
 * texture_index - Pointer to an unsigned int updated with where the texture lies within the batch renderer's texture array.
 * buffer_pointer - A pointer to a pointer of a vertex struct updated to the quad_pointer.
 */
extern void batchQuad(Batcher *batcher, U32 texture_id, U32 *texture_index, void **buffer_pointer);
