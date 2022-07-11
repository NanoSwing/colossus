#pragma once

#include "colossus/core/defs.h"
#include "colossus/core/math/vec2.h"

/*
 * Opaque Graphics structure.
 */
typedef struct Graphics Graphics;

/*
 * Camera object.
 */
typedef struct {
    /* Position. */
    Vec2 position;
    /* Scale. */
    F32 scale;
} Camera;

/*
 * Creates a graphics object.
 *
 * width - Window width.
 * height - Window height.
 * title - Window title.
 * resizable - Is the window resizable.
 * camera - Inputed camera to be configured.
 * 
 * Returnes configured graphics object.
 */
extern Graphics *graphicsCreate(I32 width, I32 height, const char *title, B8 resizable, Camera **camera);
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

/*
 * Toggles window fullscreen on current monitor.
 *
 * graphics - Graphics object.
 */
extern void graphicsToggleFullscreen(Graphics *graphics);
