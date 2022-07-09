#include "colossus/graphics/buffers/EBO.h"

#include <glad/glad.h>

EBO eboCreate(const int *indices, int index_count)
{
    EBO ebo;

    glGenBuffers(1, (unsigned int *) &ebo.id);
    eboBind(ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_count * sizeof(int), indices, GL_STATIC_DRAW);

    eboUnbind();
    return ebo;
}

void eboDestroy(EBO ebo)
{
    glDeleteBuffers(1, (unsigned int *) &ebo.id);
}

void eboBind(EBO ebo) { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo.id); }
void eboUnbind(void)  { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }
