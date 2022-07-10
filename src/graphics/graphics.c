#include "graphics/internal_graphics.h"
#include "colossus/core/defs.h"
#include "callbacks/callbacks.h"
#include "colossus/graphics/input.h"
#include "colossus/core/logger.h"

#include <stdlib.h>

#include <glad/glad.h>

Graphics *graphicsCreate(I32 width, I32 height, const char *title, B8 resizable, Camera **camera)
{
    Graphics *graphics = malloc(sizeof(Graphics));
    graphics->cam.position = vec2s(0.0f);
    graphics->cam.scale = 1.0f;
    *camera = &graphics->cam;

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
    glfwSetMouseButtonCallback(graphics->window, mouseButtonCallback);
    glfwSwapInterval(0);

    // Init glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        logError("Glad failed.");
    }

    return graphics;
}

void graphicsDestroy(Graphics *graphics)
{
    glfwDestroyWindow(graphics->window);
    glfwTerminate();
    free(graphics);
}

void graphicsLoop(Graphics *graphics, void (*user_function)(void *args), void *args)
{
    while (!glfwWindowShouldClose(graphics->window)) {
        // Update graphics window size.
        glfwGetFramebufferSize(graphics->window, &graphics->width, &graphics->height);

        user_function(args);

        // Update mouse and keyboard state since it's no longer the first frame of being pressed.
        for (I32 i = 0; i < GLFW_KEY_LAST; i++) {
            keyboard[i].first = false;
        }
        for (I32 i = 0; i < 3; i++) {
            mouse[i].first = false;
        }

        glfwSwapBuffers(graphics->window);
        glfwPollEvents();
    }
}
