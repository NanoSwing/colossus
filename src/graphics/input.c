#include "colossus/graphics/input.h"

Key keyboard[348] = {0};
Key mouse[3] = {0};

/*
 * Is first frame of being updated and is pressed.
 */
B8 keyDown(KeyCode key_code) { return (keyboard[key_code].pressed && keyboard[key_code].first); }
/*
 * Is pressed.
 */
B8 keyHold(KeyCode key_code) { return keyboard[key_code].pressed; }
/*
 * Is first frame of being updated and is not pressed.
 */
B8 keyUp(KeyCode key_code) { return (!keyboard[key_code].pressed && keyboard[key_code].first); }

/*
 * Is first frame of being updated and is pressed.
 */
B8 mouseButtonDown(MouseButtonCode mouse_button) { return (mouse[mouse_button].pressed && mouse[mouse_button].first); }
/*
 * Is pressed.
 */
B8 mouseButton(MouseButtonCode mouse_button)     { return mouse[mouse_button].pressed; }
/*
 * Is first frame of being updated and is not pressed.
 */
B8 mouseButtonUp(MouseButtonCode mouse_button)   { return (!mouse[mouse_button].pressed && mouse[mouse_button].first); }
