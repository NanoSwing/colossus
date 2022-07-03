#pragma once

#include "colossus/core/defs.h"

/*
 * Describes how a texture should be scaled.
 */
typedef enum {
    /* Scales each pixel without interpolation. Best used with pixel art. */
    MIN_MAG_NEAREST,
    /* Scales pixels with linear interpolation. Best used with higher resolution images. */
    MIN_MAG_LINEAR
} MinMagFilter;

/*
 * Structure represneting a texture.
 */
typedef struct {
    /* OpenGL texture id. */
    U32 id;
    /* Texture width. */
    I32 width;
    /* Texture height. */
    I32 height;
} Texture;
/*
 * Loads a texture from a specified path.
 *
 * path - Path to image.
 * filter - How the image should be scaled.
 * 
 * Returns the requested texture. If loading fails, it will return a texture object with a negative width and height and an id of 0.
 */
extern Texture textureLoad(const char *path, MinMagFilter filter);
/*
 * Wrapper for OpenGL call to destoy texture.
 */
extern void textureDestroy(Texture texture);
