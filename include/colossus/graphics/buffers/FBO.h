#pragma once

#include "colossus/core/defs.h"
#include "colossus/graphics/textures.h"

typedef struct {
    I32 id;
    Texture color_attachment;
    I32 width, height;
} FBO;

extern FBO fboCreate(I32 width, I32 height, Texture color_attachment);
extern void fboDestroy(FBO fbo);

extern void fboResize(FBO fbo);

extern void fboBind(FBO fbo);
extern void fboUnbind(void);
