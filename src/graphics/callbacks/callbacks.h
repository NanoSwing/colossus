#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

extern void framebufferSizeCallback(GLFWwindow* window, int width, int height);
extern void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
extern void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
