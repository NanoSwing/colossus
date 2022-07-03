#pragma once
#include "colossus/graphics/graphics.h"
#include "graphics/batcher.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

typedef struct {
    GLFWwindow *window;
    GraphicsConfig config;

    Batcher quad_batcher;
    Mat4 projection;

    Batcher line_batcher;
} GraphicsContext;

/* Global graphics context. */
extern GraphicsContext g_context;

typedef struct {
    Vec2 position;
    Vec4 color;
    float texture_id;
    Vec2 texture_coords;
} Vertex;

typedef struct {
    Vec2 position;
    Vec4 color;
} LineVertex;

extern void drawQuad(Vec2 pos, Vec2 size, F32 rotation, Vec4 color, Texture texture, I32 frame_count, I32 frame);
