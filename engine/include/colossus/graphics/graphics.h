#pragma once

#include "colossus/core/defs.h"
#include "colossus/core/math/vec2.h"
#include "colossus/core/math/vec4.h"
#include "colossus/graphics/texture.h"

typedef struct {
    I32 width;
    I32 height;
    F32 scale;
    const char *title;
    B8 resizable;

    F32 red;
    F32 green;
    F32 blue;
} GraphicsConfig;

extern void initGraphics(GraphicsConfig config);
extern void terminateGraphics(void);

extern B8 graphicsRunning(void);
extern void graphicsLoopBegin(void);
extern void graphicsLoopEnd(void);

extern void beginBatch(void);
extern void flushBatch(void);
extern void endBatch(void);

extern void drawColor(Vec2 pos, Vec2 size, F32 rotation, Vec4 color);
extern void drawTexture(Vec2 pos, Vec2 size, F32 rotation, Texture texture);
extern void drawSpriteSheet(Vec2 pos, Vec2 size, F32 rotation, SpriteSheet sheet, I32 frame);
