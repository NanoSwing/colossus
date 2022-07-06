#include "graphics/callbacks.h"
#include "graphics/internal_input.h"

#include <glad/glad.h>

/*
 * Resize window viewport when window resizes.
 */
void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    (void) window;
    glViewport(0, 0, width, height);
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    (void) window;
    (void) scancode;
    (void) mods;

    if (action == GLFW_RELEASE) {
        keyboard[key].first = true;
        keyboard[key].pressed = false;
    } else if (action == GLFW_PRESS) {
        keyboard[key].first = true;
        keyboard[key].pressed = true;
    }
}
