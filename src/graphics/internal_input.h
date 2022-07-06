#pragma once

#include "colossus/graphics/input.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

typedef struct {
    B8 pressed;
    B8 first;
} Key;

extern Key keyboard[GLFW_KEY_LAST];
