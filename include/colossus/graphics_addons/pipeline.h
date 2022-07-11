#pragma once

#include "colossus/graphics/graphics.h"
#include "colossus/graphics/batcher.h"
#include "colossus/graphics/shaders.h"
#include "colossus/graphics/textures.h"
#include "colossus/graphics/buffers/FBO.h"
#include "colossus/core/math/vec2.h"
#include "colossus/ecs/ecs.h"

/*
 * Vertex.
 */
typedef struct {
    /* Position. */
    Vec2 pos;
    /* UV coordinates. */
    Vec2 uv;
    /* Texture ID. */
    float tex_id;
    /* Color. */
    Vec4 color;
} Vertex;

/*
 * Opaque pipline structure.
 */
typedef struct Pipeline Pipeline;

/*
 * Pipline create.
 *
 * graphics - Graphics to use.
 * pixels_per_unit - Pixels per unit when rendering.
 *
 * Returns pipeline object.
 */
extern Pipeline *pipelineCreate(Graphics *graphics);
/*
 * Destroy pipeline.
 * Make sure to destroy pipeline before graphics.
 * 
 * pipeline - Pipeline.
 */
extern void pipelineDestroy(Pipeline *pipeline);

/*
 * Render pipeline.
 *
 * pipeline - Pipeline.
 * ecs - ECS with graphics addon.
 */
extern void pipelineRender(Pipeline *pipeline, ECS *ecs);

/*
 * Add a quad to pipeline batcher buffer.
 *
 * pipeline - Pipeline.
 * position - Position.
 * size - Size.
 * rotation - Rotation in degrees.
 * color - Color.
 * texture - Texture.
 * frame_count - Amount of frames in texture.
 * frame - Current frame.
 */
extern void drawQuad(Pipeline *pipeline, Vec2 position, Vec2 size, F32 rotation, Vec4 color, Texture texture, I32 frame_count, I32 frame);

/*
 * Draw a line starting from a point and extruding a certain length.
 *
 * start - Starting position.
 * length - Length.
 * angle - Angle in degrees.
 * thickness - Thickness.
 * color - Color.
 */
extern void drawLineLength(Pipeline *pipeline, Vec2 start, F32 length, F32 angle, F32 thickness, Vec4 color);
/*
 * Draw a line between two points.
 *
 * a - Position a.
 * b - Position b.
 * thickness - Thickness.
 * color - Color.
 */
extern void drawLinePoints(Pipeline *pipeline, Vec2 a, Vec2 b, F32 thickness, Vec4 color);
