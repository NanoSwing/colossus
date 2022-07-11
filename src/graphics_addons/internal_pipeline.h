#pragma once

#include "colossus/graphics_addons/pipeline.h"

typedef struct {
    Vec2 a;
    Vec2 b;
    F32 thickness;
    Vec4 color;
} LineCall;

struct Pipeline {
    Graphics *graphics;
    Batcher batcher;
    Shader shader;
    Texture textures[32];
    I32 texture_count;

    LineCall *lines;

    Shader quad_shader;
    FBO screen_fbo;
    VBO quad_vbo;
    EBO quad_ebo;
    VAO quad_vao;
};
