#pragma once

#include "colossus/core/defs.h"

typedef struct {
    I32 id;
    U64 vertex_size;
    B8 dynamic;
} VBO;

extern VBO vboCreateDynamic(U64 vertex_size, I32 vertex_count);
extern VBO vboCreateStatic(U64 vertex_size, I32 vertex_count, const void *vertices);
extern void vboDestroy(VBO vbo);

extern void vboSendData(VBO vbo, const void *data, U64 data_size);
extern void vboBind(VBO vbo);
extern void vboUnbind(void);
