#include "colossus/graphics/input.h"

Key keyboard[348] = {0};
Key mouse[3] = {0};

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

B8 mouseButtonDown(MouseButtonCode mouse_button)
{
    if (mouse[mouse_button].pressed && mouse[mouse_button].first) {
        return true;
    }
    return false;
}

B8 mouseButton(MouseButtonCode mouse_button)
{
    return mouse[mouse_button].pressed;
}

B8 mouseButtonUp(MouseButtonCode mouse_button)
{
    if (!mouse[mouse_button].pressed && mouse[mouse_button].first) {
        return true;
    }

    return false;
}
