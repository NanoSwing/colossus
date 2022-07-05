#pragma once

#include "colossus/core/defs.h"
#include "colossus/core/math/vec2.h"
#include "colossus/core/math/vec3.h"
#include "colossus/core/math/vec4.h"
#include "colossus/graphics/texture.h"

/*
 * Structure containing information used when initializing graphics with graphicsInit().
 */
typedef struct {
    /* Width of window. */
    I32 width;
    /* Height of window. */
    I32 height;
    /* How many units the window can fit vertically. */
    F32 scale;
    /* Title of window. */
    const char *title;
    /* Can the window be resized. */
    B8 resizable;
    /* Background color of window. */
    Vec3 background_color;
} GraphicsConfig;

/*
 * Creates a window and initializes the neccessary systems to use draw functions.
 *
 * config - Graphics configuration.
 */
extern void graphicsInit(GraphicsConfig config);
/*
 * Stop the graphics, destroying the window.
 */
extern void graphicsTerminate(void);

/*
 * Check whether the graphics is running or a stop command has been sent such as a window close event.
 *
 * Returns 1/true if it's still running, 0/false if not.
 */
extern B8 graphicsRunning(void);
/*
 * Clears the previous render and should be ran before any draw commands.
 */
extern void graphicsLoopBegin(void);
/*
 * Polls for window events and displays what has been rendered.
 */
extern void graphicsLoopEnd(void);

/*
 * Prepares the graphics pipeline for rendering.
 */
extern void beginBatch(void);
/*
 * Makes a render call to the GPU to render the batch.
 */
extern void flushBatch(void);
/*
 * Tells the GPU how big the batch is. This should be ran before flushing.
 */
extern void endBatch(void);

/*
 * Draws a quad with a specified color.
 *
 * pos - Position.
 * size - Size.
 * rotation - Rotation.
 * color - Color
 */
extern void drawColor(Vec2 pos, Vec2 size, F32 rotation, Vec4 color);
/*
 * Draws quad with a specified texture.
 *
 * pos - Position.
 * size - Size.
 * rotation - Rotation.
 * texture - Texture.
 */
extern void drawTexture(Vec2 pos, Vec2 size, F32 rotation, Texture texture);
/*
 * Draws a quad with a specified frame of a sprite sheet.
 *
 * pos - Position.
 * size - Size.
 * rotation - Rotation.
 * sheet - Sprite sheet texture.
 * frame_count - Amount of frames in sprite sheet.
 * frame - Which frame of the sprite sheet.
 */
extern void drawSpriteSheet(Vec2 pos, Vec2 size, F32 rotation, Texture sheet, I32 frame_count, I32 frame);

/*
 * Draws a line between two coordinates.
 *
 * start - Beginning of line.
 * end - End of line.
 * thickness - Thickness.
 * color - Color.
 */
extern void drawLinePoints(Vec2 start, Vec2 end, F32 thickness, Vec4 color);
/*
 * Draws a line from a position with a length and an angle, starting from pointing straight up.
 *
 * start - Beginning of line.
 * length - Length.
 * angle - Angle in degrees.
 * thickness - Thickness.
 * color - Color.
 */
extern void drawLineLength(Vec2 start, F32 length, F32 angle, F32 thickness, Vec4 color);
