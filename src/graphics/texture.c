#include "colossus/graphics/texture.h"
#include "colossus/core/logger.h"

#include <glad/glad.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

Texture textureLoad(const char *path, MinMagFilter filter)
{
    Texture texture;
    texture.id = 0;
    texture.width = -1;
    texture.height = -1;

    // Load image
    I32 nr_channels;
    stbi_set_flip_vertically_on_load(true);
    U8 *data = stbi_load(path, &texture.width, &texture.height, &nr_channels, 0);
    if (data == NULL) {
        logWarn("Unable to load image: '%s'", path);
        return texture;
    }

    I32 _filter = 0;
    switch (filter)
    {
    case MIN_MAG_LINEAR:
        _filter = GL_LINEAR;
        break;
    case MIN_MAG_NEAREST:
        _filter = GL_NEAREST;
    default:
        break;
    }

    // Create texture
    glGenTextures(1, &texture.id);
    glBindTexture(GL_TEXTURE_2D, texture.id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // Nearest for pixel art
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, _filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, _filter);
    U32 format = nr_channels == 3 ? GL_RGB : GL_RGBA;
    glTexImage2D(GL_TEXTURE_2D, 0, format, texture.width, texture.height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);

    return texture;
}

void textureDestroy(Texture texture)
{
    glDeleteTextures(1, &texture.id);
}
