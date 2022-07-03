#pragma once

#include "colossus/core/defs.h"

typedef struct {
    U32 id;
    I32 width;
    I32 height;
} Texture;
extern Texture textureLoad(const char *path);
extern void textureDestroy(Texture texture);

typedef struct {
    Texture texture;
    I32 frame_count;
} SpriteSheet;
extern SpriteSheet spriteSheetLoad(const char *path, I32 frame_count);
extern void spriteSheetDestroy(SpriteSheet sheet);
