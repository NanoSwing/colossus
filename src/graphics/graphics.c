#include "graphics/internal_graphics.h"
#include "colossus/core/defs.h"
#include "callbacks/callbacks.h"
#include "colossus/graphics/input.h"
#include "colossus/core/logger.h"

#include <stdlib.h>

#include <glad/glad.h>

Graphics *graphicsInit(I32 width, I32 height, const char *title, B8 resizable)
{
    Graphics *graphics = malloc(sizeof(graphics));

    // Init GLFW
    if (!glfwInit()) {
        logError("GLFW failed.");
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, resizable);

    // Create window
    graphics->window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (graphics->window == NULL) {
        logError("Window failed.");
    }
    glfwMakeContextCurrent(graphics->window);
    glfwSetFramebufferSizeCallback(graphics->window, framebufferSizeCallback);
    glfwSetKeyCallback(graphics->window, keyCallback);
    glfwSwapInterval(0);

    // Init glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        logError("Glad failed.");
    }

    return graphics;
}

void graphicsTerminate(Graphics *graphics)
{
    glfwDestroyWindow(graphics->window);
    glfwTerminate();
    free(graphics);
}

void graphicsLoop(Graphics *graphics, void (*user_function)(void *args), void *args)
{
    while (!glfwWindowShouldClose(graphics->window)) {
        glfwGetFramebufferSize(graphics->window, &graphics->width, &graphics->height);

        user_function(args);

        for (I32 i = 0; i < GLFW_KEY_LAST; i++) {
            keyboard[i].first = false;
        }

        glfwSwapBuffers(graphics->window);
        glfwPollEvents();
    }
}
