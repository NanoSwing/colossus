#pragma once

#include "colossus/core/defs.h"

/*
 * Equvilant of NULL for textures.
 */
#define NULL_TEXTURE (Texture) {.id = -1, .width = -1, .height = -1}
/*
 * Check if texture is a NULL_TEXTURE.
 */
#define textureIsNULL(texture) (texture.id == NULL_TEXTURE.id && texture.width == NULL_TEXTURE.width && texture.height == NULL_TEXTURE.height)

/*
 * Texture scaling method.
 */
typedef enum {
    /* Nearest best used with pixel art. */
    SCALE_NEAREST,
    /* Linear best used with larget art. */
    SCALE_LINEAR
} TextureScaling;

/*
 * Texture.
 */
typedef struct {
    /* Width. */
    I32 width;
    /* Height. */
    I32 height;
    /* ID. */
    I32 id;
    /* Format of texture. 4 for RGBA, 3 for RGB. */
    I32 format;
    /* Scaling method. */
    I32 scaler;
} Texture;

/*
 * Create a texture from a file.
 *
 * path - File path to image.
 * scaling - Scaling method.
 * 
 * Returns created texture. Returns NULL_TEXTURE if fails.
 */
extern Texture textureFromFile(const char *path, TextureScaling scaling);
/*
 * Creates a texture from provided pixel data.
 *
 * width - Width.
 * height - Height.
 * scaling - Scaling method.
 * channels - Color channels. 4 for RGBA, 3 for RGB.
 * pixels - Pixel data.
 * 
 * Returns created texture. Returns NULL_TEXTURE if fails.
 */
extern Texture textureFromPixels(I32 width, I32 height, TextureScaling scaling, I8 channels, const void *pixels);

/*
 * Destroy texture.
 */
extern void textureDestroy(Texture texture);

/*
 * Bind/use texture.
 *
 * texture - Texture.
 */
extern void textureBind(Texture texture);
/*
 * Unbind/stop using any texture.
 */
extern void textureUnbind(void);
/*
 * Bind texture at specific spot/unit.
 *
 * unit - Texture unit.
 * texture - Texture.
 */
extern void textureBindUnit(I32 unit, Texture texture);
/*
 * Resize/reallocate texture space.
 * 
 * texture - Texture.
 * width - Width.
 * height - Height.
 * pixels - Pixel data.
 */
extern void textureResize(Texture *texture, I32 width, I32 height, const void *pixels);
