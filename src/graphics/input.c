#include "colossus/graphics/input.h"

Key keyboard[348] = {0};

B8 keyDown(KeyCode key_code)
{
    if (keyboard[key_code].pressed && keyboard[key_code].first) {
        return true;
    }

    return false;
}

B8 keyHold(KeyCode key_code)
{
    return keyboard[key_code].pressed;
}

B8 keyUp(KeyCode key_code)
{
    if (!keyboard[key_code].pressed && keyboard[key_code].first) {
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

B8 getMouseButtonUp(KeyCode mouse_button)
{
    (void) mouse_button;
    return false;
}
