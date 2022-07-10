#include "graphics/callbacks/callbacks.h"
#include "colossus/graphics/input.h"

#include <glad/glad.h>

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

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    (void) window;
    (void) mods;

    if (action == GLFW_RELEASE) {
        mouse[button].first = true;
        mouse[button].pressed = false;
    } else if (action == GLFW_PRESS) {
        mouse[button].first = true;
        mouse[button].pressed = true;
    }
}
