#pragma once

#include "colossus/core/defs.h"
#include "colossus/graphics/textures.h"

/*
 * Framebuffer object.
 */
typedef struct {
    /* ID. */
    I32 id;
    /* Texture containing color data. Used to render to. */
    Texture color_attachment;
} FBO;

/*
 * Create a framebuffer object.
 *
 * color_attachment - Texture to attach. Used to render to.
 * 
 * Returns framebuffer object.
 */
extern FBO fboCreate(Texture color_attachment);
/*
 * Destroy a framebuffer object.
 *
 * fbo - Framebuffer object.
 */
extern void fboDestroy(FBO fbo);

/*
 * Bind / use framebuffer object.
 *
 * fbo - Framebuffer obejct.
 */
extern void fboBind(FBO fbo);
/*
 * Unbind / stop using any framebuffer object.
 */
extern void fboUnbind(void);
