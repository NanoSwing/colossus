#include "colossus/graphics/buffers/VBO.h"
#include "colossus/core/logger.h"

#include <stdlib.h>
#include <glad/glad.h>

VBO vboCreateDynamic(U64 vertex_size, I32 vertex_count)
{
    VBO vbo = {0};
    vbo.dynamic = true;
    vbo.vertex_size = vertex_size;

    glGenBuffers(1, (U32 *) &vbo.id);
    vboBind(vbo);

    glBufferData(GL_ARRAY_BUFFER, vertex_size * vertex_count, NULL, GL_DYNAMIC_DRAW);

    vboUnbind();

    return vbo;
}

VBO vboCreateStatic(U64 vertex_size, I32 vertex_count, const void *vertices)
{
    VBO vbo = {0};
    vbo.dynamic = false;
    vbo.vertex_size = vertex_size;

    glGenBuffers(1, (U32 *) &vbo.id);
    vboBind(vbo);

    glBufferData(GL_ARRAY_BUFFER, vertex_size * vertex_count, vertices, GL_STATIC_DRAW);

    vboUnbind();

    return vbo;
}

void vboDestroy(VBO vbo)
{
    glDeleteBuffers(1, (U32 *) &vbo.id);
}

void vboSendData(VBO vbo, const void *data, U64 data_size)
{
    if (!vbo.dynamic) {
        logWarn("Unable to send data to a static VBO.");
        return;
    }

    vboBind(vbo);
    glBufferSubData(GL_ARRAY_BUFFER, 0, data_size, data);
}

void vboBind(VBO vbo) { glBindBuffer(GL_ARRAY_BUFFER, vbo.id); }
void vboUnbind(void)  { glBindBuffer(GL_ARRAY_BUFFER, 0); }
