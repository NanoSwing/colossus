#include <stdio.h>

#include <GLFW/glfw3.h>

int main(void)
{
    if (glfwInit()) {
        printf("GLFW working!\n");
    } else {
        printf("GLFW failed!\n");
    }
    
    return 0;
}
