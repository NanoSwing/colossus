#pragma once

#include "colossus/core/defs.h"
#include "colossus/graphics/buffers/VBO.h"
#include "colossus/graphics/buffers/EBO.h"

typedef struct {
    U64 offset;
    U64 size;
} VertexLayout;

typedef struct {
    I32 id;
    VBO vbo;
} VAO;

extern VAO vaoCreate(void);
extern void vaoDestroy(VAO vao);

extern void vaoBind(VAO vao);
extern void vaoUnbind(void);

extern void vaoAddVBO(VAO vao, VBO vbo, U64 vertex_size, const VertexLayout *layout, I32 layout_count);
extern void vaoAddEBO(VAO vao, EBO ebo);
