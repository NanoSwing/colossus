#pragma once

#include "colossus/core/defs.h"

typedef struct {
    I32 width;
    I32 height;
    const char *title;
    B8 resizable;

    F32 red;
    F32 green;
    F32 blue;
} GraphicsConfig;

extern void initGraphics(GraphicsConfig config);
extern void terminateGraphics(void);

extern B8 graphicsRunning(void);
extern void graphicsLoop(void);
