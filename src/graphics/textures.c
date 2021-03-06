#include "colossus/graphics/textures.h"
#include "colossus/core/logger.h"

#include <glad/glad.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

Texture textureFromFile(const char *path, TextureScaling scaling)
{
    Texture texture;

    I32 width, height, channels;
    // Images are loaded verticaly for some reason so flip it
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load(path, &width, &height, &channels, 0);
    if (!data) {
        logWarn("Unable to load texutre: '%s'", path);
        return NULL_TEXTURE;
    }

    // Create texture
    texture = textureFromPixels(width, height, scaling, channels, data);
    stbi_image_free(data);

    textureBind(texture);
    glGenerateMipmap(GL_TEXTURE_2D);
    textureUnbind();

    return texture;
}

Texture textureFromPixels(I32 width, I32 height, TextureScaling scaling, I8 channels, const void *pixels)
{
    // Get GL format from channels.
    I32 format = channels == 3 ? GL_RGB : channels == 4 ? GL_RGBA : -1;
    if (format == -1) {
        logWarn("Unsupported channel count.");
        return NULL_TEXTURE;
    }
    // Get GL scale from TextureScaling enum
    I32 scaler = scaling == SCALE_LINEAR ? GL_LINEAR : GL_NEAREST;

    // Configure texture
    Texture texture;
    texture.width = width;
    texture.height = height;
    texture.format = format;
    texture.scaler = scaler;
    
    glGenTextures(1, (U32 *) &texture.id);
    textureBind(texture);

    // Configure texture filtering and clamping
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, scaler);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, scaler);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    // Generate texture
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, pixels);

    textureUnbind();
    return texture;
}

void textureDestroy(Texture texture) { glDeleteTextures(1, (U32 *) &texture.id); }
void textureBind(Texture texture) { glBindTexture(GL_TEXTURE_2D, texture.id); }
void textureUnbind(void) { glBindTexture(GL_TEXTURE_2D, 0); }
void textureBindUnit(I32 unit, Texture texture) { glBindTextureUnit(unit, texture.id); }

void textureResize(Texture *texture, I32 width, I32 height, const void *pixels)
{
    textureBind(*texture);
    texture->width = width;
    texture->height = height;
    
    // Reallocate texture
    glTexImage2D(GL_TEXTURE_2D, 0, texture->format, width, height, 0, texture->format, GL_UNSIGNED_BYTE, pixels);
    
    textureUnbind();
}
