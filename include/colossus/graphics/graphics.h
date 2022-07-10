#pragma once

#include "colossus/core/defs.h"

/*
 * Opaque Graphics structure.
 */
typedef struct Graphics Graphics;

/*
 * Creates a graphics object.
 *
 * width - Window width.
 * height - Window height.
 * title - Window title.
 * resizable - Is the window resizable.
 * 
 * Returnes configured graphics object.
 */
extern Graphics *graphicsCreate(I32 width, I32 height, const char *title, B8 resizable);
/*
 * Destroy graphics.
 *
 * graphics - Graphics object.
 */
extern void graphicsDestroy(Graphics *graphics);

/*
 * Starts a while loop until window recieves a close event.
 *
 * graphics - Graphics object.
 * user_function - Function executed within loop.
 * args - Arguments sent to the user function.
 */
extern void graphicsLoop(Graphics *graphics, void (*user_function)(void *args), void *args);
