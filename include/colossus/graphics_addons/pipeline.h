#pragma once

#include "colossus/graphics/graphics.h"
#include "colossus/graphics/batcher.h"
#include "colossus/graphics/shaders.h"
#include "colossus/graphics/textures.h"
#include "colossus/graphics/buffers/FBO.h"
#include "colossus/core/math/vec2.h"
#include "colossus/ecs/ecs.h"

typedef struct {
    Vec2 pos;
    Vec2 uv;
    float tex_id;
    Vec4 color;
} Vertex;

typedef struct Pipeline Pipeline;

extern Pipeline *pipelineCreate(Graphics *graphics);
extern void pipelineDestroy(Pipeline *pipeline);

extern void pipelineRender(Pipeline *pipeline, ECS *ecs);

extern void drawQuad(Pipeline *pipeline, Vec2 position, Vec2 size, F32 rotation, Vec4 color, Texture texture);

typedef struct {
    Vec2 pos;
    Vec4 color;
} Quad;
extern Quad draw_grid[100][100];
