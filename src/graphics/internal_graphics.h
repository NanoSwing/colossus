#pragma once
#include "colossus/graphics/graphics.h"
#include "graphics/batcher.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

/*
 * Structure containing graphics data.
 */
typedef struct {
    /* Window. */
    GLFWwindow *window;
    /* Config. */
    GraphicsConfig config;

    /* Quad batcher. */
    Batcher quad_batcher;
    /* Line batcher. */
    Batcher line_batcher;

    /* Projection for rendering. */
    Mat4 projection;
} GraphicsContext;

/* Global graphics context declaration. */
extern GraphicsContext g_context;

/*
 * Structure for a quad vertex.
 */
typedef struct {
    /* Position. */
    Vec2 position;
    /* Color. */
    Vec4 color;
    /* What index of the texture array to use. */
    float texture_id;
    /* Where from the texture it should render. Also called UV. */
    Vec2 texture_coords;
} Vertex;

/*
 * Structure for a line vertex.
 */
typedef struct {
    /* Position. */
    Vec2 position;
    /* Color. */
    Vec4 color;
} LineVertex;

/*
 * Adds a quad to the batch.
 *
 * pos - Position.
 * size - Size.
 * rotation - Rotation.
 * color - Color.
 * texture - Texture / sprite sheet.
 * frame_count - Amount of frames within the texture.
 * frame - What frame to render from the texture.
 */
extern void drawQuad(Vec2 pos, Vec2 size, F32 rotation, Vec4 color, Texture texture, I32 frame_count, I32 frame);
