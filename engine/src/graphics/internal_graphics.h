#pragma once
#include "colossus/graphics/graphics.h"
#include "graphics/batcher.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

typedef struct {
    GLFWwindow *window;
    GraphicsConfig config;

    Batcher batcher;
    Mat4 projection;
} GraphicsContext;

/* Global graphics context. */
extern GraphicsContext g_context;

typedef struct {
    Vec2 position;
    Vec4 color;
    float texture_id;
    Vec2 texture_coords;
} Vertex;
