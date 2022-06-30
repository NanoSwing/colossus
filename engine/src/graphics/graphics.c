#include "graphics/internal_graphics.h"
#include "colossus/core/logger.h"

#include <malloc.h>

#include <glad/glad.h>

/* Define global graphics context. */
GraphicsContext g_context = { 0 };

void initGraphics(GraphicsConfig config)
{
    g_context.config = config;

    if (!glfwInit()) {
        logFatal("GLFW failed to initialize!");
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, config.resizable);
    // Turn off fps limit
    glfwSwapInterval(0);

    g_context.window = glfwCreateWindow(config.width, config.height, config.title, NULL, NULL);
    if (g_context.window == NULL) {
        terminateGraphics();
        logFatal("Window creation failed!");
    }
    glfwMakeContextCurrent(g_context.window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        terminateGraphics();
        logFatal("Glad failed to initialize!");
    }
    glViewport(0, 0, config.width, config.height);

    logInfo("Graphics initialized successfully!");
}

void terminateGraphics(void)
{
    if (g_context.window != NULL) {
        glfwDestroyWindow(g_context.window);
    }
    glfwTerminate();
}


B8 graphicsRunning(void)
{
    return !glfwWindowShouldClose(g_context.window);
}

void graphicsLoop(void)
{
    glClearColor(g_context.config.red, g_context.config.green, g_context.config.blue, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(g_context.window);

    glfwPollEvents();
}
