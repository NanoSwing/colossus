#include "colossus/graphics/buffers/FBO.h"

#include <glad/glad.h>

FBO fboCreate(I32 width, I32 height, Texture color_attachment)
{
    FBO fbo;
    fbo.width = width;
    fbo.height = height;
    fbo.color_attachment = color_attachment;

    glGenFramebuffers(1, (U32 *) &fbo.id);
    fboBind(fbo);
    
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, color_attachment.id, 0);

    fboUnbind();

    return fbo;
}

void fboDestroy(FBO fbo) { glDeleteFramebuffers(1, (U32 *) &fbo.id); }
void fboBind(FBO fbo) { glBindFramebuffer(GL_FRAMEBUFFER, fbo.id); }
void fboUnbind(void) { glBindFramebuffer(GL_FRAMEBUFFER, 0); }
