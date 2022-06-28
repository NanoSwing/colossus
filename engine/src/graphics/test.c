#include "colossus/graphics/graphics.h"

#include <stdio.h>

#include <GLFW/glfw3.h>

void testGraphics(void)
{
    if (glfwInit()) {
        printf("GLFW initialized successfully!\n");
    } else {
        printf("GLFW sadge!\n");
    }

    glfwTerminate();
}
