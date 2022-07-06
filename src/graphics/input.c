#include "colossus/graphics/input.h"
#include "graphics/internal_input.h"

Key keyboard[GLFW_KEY_LAST] = {0};

B8 keyDown(KeyCode key_code)
{
    if (keyboard[key_code].pressed && keyboard[key_code].first) {
        keyboard[key_code].first = false;
        return true;
    }

    return false;
}

B8 keyHold(KeyCode key_code)
{
    return keyboard[key_code].pressed;
}

B8 keyRelease(KeyCode key_code)
{
    if (!keyboard[key_code].pressed && keyboard[key_code].first) {
        keyboard[key_code].first = false;
        return true;
    }

    return false;
}

B8 getMouseButtonDown(KeyCode mouse_button)
{
    (void) mouse_button;
    return false;
}

B8 getMouseButton(KeyCode mouse_button)
{
    (void) mouse_button;
    return false;
}

B8 getMouseButtonRelease(KeyCode mouse_button)
{
    (void) mouse_button;
    return false;
}
