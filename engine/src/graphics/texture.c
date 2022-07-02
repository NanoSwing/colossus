#include "colossus/graphics/texture.h"
#include "colossus/core/logger.h"

#include <glad/glad.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

Texture textureLoad(const char *path)
{
    // Load image
    I32 width, height, nr_channels;
    stbi_set_flip_vertically_on_load(true);
    U8 *data = stbi_load(path, &width, &height, &nr_channels, 0);
    if (data == NULL) {
        logWarn("Unable to load image: '%s'", path);
        return 0;
    }

    // Create texture
    Texture texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    U32 format = nr_channels == 3 ? GL_RGB : GL_RGBA;
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);

    return texture;
}

void textureDestroy(Texture texture)
{
    glDeleteTextures(1, &texture);
}
