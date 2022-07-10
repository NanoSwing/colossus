#include "colossus/graphics/buffers/VAO.h"

#include <glad/glad.h>

VAO vaoCreate(void)
{
    VAO vao = {0};

    glGenVertexArrays(1, (U32 *) &vao.id);

    return vao;
}

void vaoDestroy(VAO vao)
{
    glDeleteVertexArrays(1, (U32 *) &vao.id);
}


void vaoBind(VAO vao)
{
    glBindVertexArray(vao.id);
}

void vaoUnbind(void)
{
    glBindVertexArray(0);
}

void vaoAddVBO(VAO vao, VBO vbo, U64 vertex_size, const VertexLayout *layout, I32 layout_count)
{
    vaoBind(vao);
    vboBind(vbo);

    for (I32 i = 0; i < layout_count; i++) {
        glVertexAttribPointer(i, layout[i].size, GL_FLOAT, GL_FALSE, vertex_size, (const void *) layout[i].offset);
        glEnableVertexAttribArray(i);
    }

    vboUnbind();
    vaoUnbind();
}

void vaoAddEBO(VAO vao, EBO ebo)
{
    vaoBind(vao);
    eboBind(ebo);

    vaoUnbind();
    eboUnbind();
}
