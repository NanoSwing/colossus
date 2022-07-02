#include "graphics/batcher.h"
#include "colossus/core/da.h"

#include <stddef.h>
#include <malloc.h>
#include <string.h>

#include <glad/glad.h>

Batcher createBatcher(U32 max_quads, U64 vertex_size, const Layout *layout, Mat4 *projection, Shader shader)
{
    Batcher batcher;
    batcher.max_quads = max_quads;
    batcher.quad_count = 0;
    batcher.quad_buffer = malloc(vertex_size * max_quads * 4);
    batcher.quad_pointer = batcher.quad_buffer;
    batcher.vertex_size = vertex_size;
    batcher.shader = shader;
    batcher.projection = projection;

    // Create vertex array
    glGenVertexArrays(1, &batcher.vertex_array);
    glBindVertexArray(batcher.vertex_array);

    // Configure vertex buffer
    glGenBuffers(1, &batcher.vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, batcher.vertex_buffer);

    glBufferData(GL_ARRAY_BUFFER, vertex_size * max_quads * 4, NULL, GL_DYNAMIC_DRAW);

    for (U32 i = 0; i < daCount(layout); i++) {
        glVertexAttribPointer(i, layout[i].size, GL_FLOAT, GL_FALSE, vertex_size, (const void *) layout[i].offset);
        glEnableVertexAttribArray(i);
    }

    // Configure element buffer
    glGenBuffers(1, &batcher.element_array);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, batcher.element_array);

    U32 indices[max_quads * 6];
    U32 offset = 0;
    for (U32 i = 0; i < max_quads * 6; i += 6) {
        indices[i + 0] = offset + 0;
        indices[i + 1] = offset + 1;
        indices[i + 2] = offset + 2;

        indices[i + 3] = offset + 2;
        indices[i + 4] = offset + 3;
        indices[i + 5] = offset + 1;

        offset += 4;
    }
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Unbind everything
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    return batcher;
}

void destroyBatcher(Batcher batcher)
{
    free(batcher.quad_buffer);

    glDeleteVertexArrays(1, &batcher.vertex_array);
    glDeleteBuffers(1, &batcher.vertex_buffer);
    glDeleteBuffers(1, &batcher.element_array);
    shaderDestroy(batcher.shader);
}

void flushBatcher(Batcher *batcher)
{
    // Draw call
    glUseProgram(batcher->shader);
    shaderUniformMat4(batcher->shader, "projection", *batcher->projection);

    glBindVertexArray(batcher->vertex_array);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, batcher->element_array);

    glDrawElements(GL_TRIANGLES, batcher->quad_count * 6, GL_UNSIGNED_INT, NULL);

    batcher->quad_count = 0;
}

void startBatcher(Batcher *batcher)
{
    batcher->quad_pointer = batcher->quad_buffer;
}

void endBatcher(Batcher *batcher)
{
    U64 size = (U8 *) batcher->quad_pointer - (U8 *) batcher->quad_buffer;
    glBindBuffer(GL_ARRAY_BUFFER, batcher->vertex_buffer);
    glBufferSubData(GL_ARRAY_BUFFER, 0, size, batcher->quad_buffer);
}
