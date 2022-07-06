#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

/*
 * Resize viewport when window resizes.
 */
extern void framebufferSizeCallback(GLFWwindow* window, int width, int height);

extern void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
