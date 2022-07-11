#pragma once

#include "colossus/graphics_addons/pipeline.h"

struct Pipeline {
    Graphics *graphics;
    Batcher batcher;
    Shader shader;
    Texture textures[32];
    I32 texture_count;

    Shader quad_shader;
    FBO screen_fbo;
    VBO quad_vbo;
    EBO quad_ebo;
    VAO quad_vao;
};
