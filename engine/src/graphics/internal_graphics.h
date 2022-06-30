#pragma once
#include "colossus/graphics/graphics.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

typedef struct {
    GLFWwindow *window;
    GraphicsConfig config;
} GraphicsContext;

/* Global graphics context. */
extern GraphicsContext g_context;
