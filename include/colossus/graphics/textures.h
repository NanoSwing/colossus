#pragma once

#include "colossus/core/defs.h"

#define NULL_TEXTURE (Texture) {.id = -1, .width = -1, .height = -1}

typedef enum {
    SCALE_NEAREST,
    SCALE_LINEAR
} TextureScaling;

typedef struct {
    I32 width, height;
    I32 id;
    I32 format;
    I32 scaler;
} Texture;

extern Texture textureFromFile(const char *path, TextureScaling scaling);
extern Texture textureBlank(I32 width, I32 height, TextureScaling scaling, I8 channels, const void *pixels);

extern void textureDestroy(Texture texture);

extern void textureBind(Texture texture);
extern void textureUnbind(void);
extern void textureBindUnit(I32 unit, Texture texture);
extern void textureResize(Texture texture, I32 width, I32 height, const void *pixels);
