#include "colossus/graphics/graphics.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

struct Graphics {
    GLFWwindow *window;
    I32 width, height;
};
