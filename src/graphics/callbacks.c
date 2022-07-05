#include "graphics/callbacks.h"

#include <glad/glad.h>

/*
 * Resize window viewport when window resizes.
 */
void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    (void) window;
    glViewport(0, 0, width, height);
}
