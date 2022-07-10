#pragma once

#include "colossus/core/defs.h"
#include "colossus/graphics/buffers/VBO.h"
#include "colossus/graphics/buffers/EBO.h"

/*
 * Describes layout of a vertex sent to the shader.
 */
typedef struct {
    /* Offset in bytes from the start of struct/array. */
    U64 offset;
    /* Amount of floats. Ex, vec2 = 2 floats, float = 1 float, etc. */
    U64 size;
} VertexLayout;

/*
 * Vertex array object.
 */
typedef struct {
    /* ID. */
    I32 id;
} VAO;

/*
 * Create a vertex array object.
 *
 * Returns vertex array object.
 */
extern VAO vaoCreate(void);
/*
 * Destroy a vertex array object.
 *
 * vao - Vertex array object.
 */
extern void vaoDestroy(VAO vao);

/*
 * Bind / use vertex array object.
 *
 * vao - Vertex array object.
 */
extern void vaoBind(VAO vao);
/*
 * Unbind / stop using any vertex array object.
 */
extern void vaoUnbind(void);

/*
 * Add a vertex buffer object to a vertex array object.
 *
 * vao - Vertex array object.
 * vbo - Vertex buffer object.
 * vertex_size - Size of a vertex.
 * layout - An array of vertex layouts representing vertex structure.
 * layout_count - Objects in layout.
 */
extern void vaoAddVBO(VAO vao, VBO vbo, U64 vertex_size, const VertexLayout *layout, I32 layout_count);
