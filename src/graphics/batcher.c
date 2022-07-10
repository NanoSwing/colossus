#include "colossus/graphics/batcher.h"

#include <stdlib.h>

#include <glad/glad.h>

Batcher batcherCreate(U64 vertex_size, I32 max_vertex_count, const VertexLayout *layoyt, I32 layout_count, const I32 *indices, I32 index_count)
{
    Batcher batcher;

    batcher.vao = vaoCreate();
    batcher.vbo = vboCreateDynamic(vertex_size, max_vertex_count);
    batcher.ebo = eboCreate(indices, index_count);

    vaoAddVBO(batcher.vao, batcher.vbo, vertex_size, layoyt, layout_count);

    batcher.vertex_buffer = malloc(vertex_size * max_vertex_count);
    batcher.vertex_count = 0;
    batcher.vertex_size = vertex_size;
    batcher.max_vertex_count = max_vertex_count;

    return batcher;
}

void batcherDestroy(Batcher *batcher)
{
    vaoDestroy(batcher->vao);
    vboDestroy(batcher->vbo);
    eboDestroy(batcher->ebo);

    free(batcher->vertex_buffer);
    batcher->vertex_buffer = NULL;
}

void batcherFlush(Batcher *batcher)
{
    vboSendData(batcher->vbo, batcher->vertex_buffer, batcher->vertex_count * batcher->vertex_size);

    vaoBind(batcher->vao);
    eboBind(batcher->ebo);

    glDrawElements(GL_TRIANGLES, batcher->vertex_count / 4 * 6, GL_UNSIGNED_INT, NULL);

    vaoUnbind();
    eboUnbind();

    batcher->vertex_count = 0;
}
