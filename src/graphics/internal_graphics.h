#include "colossus/graphics/graphics.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

struct Graphics {
    /* Window. */
    GLFWwindow *window;
    /* Width of window. */
    I32 width;
    /* Height of window. */
    I32 height;
    /* Camera. */
    Camera cam;
};
