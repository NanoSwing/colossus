#include <stdio.h>

#include <GLFW/glfw3.h>

int main(void)
{
    if (glfwInit()) {
        printf("GLFW working!\n");
    } else {
        printf("GLFW failed!\n");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(1280, 720, "GLFW compilation test", NULL, NULL);
    if (window == NULL) {
        printf("Window creation failed!\n");
        glfwTerminate();
        return -1;
    }
    glfwDestroyWindow(window);

    glfwTerminate();

    return 0;
}
