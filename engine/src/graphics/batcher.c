#include "graphics/batcher.h"
#include "colossus/core/da.h"

#include <stddef.h>
#include <malloc.h>
#include <string.h>

#include <glad/glad.h>

Batcher createBatcher(U32 max_quads, U64 vertex_size, const Layout *layout, Mat4 *projection, Shader shader)
{
    Batcher batcher;
    batcher.max_quads = max_quads;
    batcher.quad_count = 0;
    batcher.quad_buffer = malloc(vertex_size * max_quads * 4);
    batcher.quad_pointer = batcher.quad_buffer;
    batcher.vertex_size = vertex_size;
    batcher.shader = shader;
    batcher.projection = projection;
    // Create a white texture
    U32 white_texture;
    glCreateTextures(GL_TEXTURE_2D, 1, &white_texture);
    glBindTexture(GL_TEXTURE_2D, white_texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    U32 color = 0xffffffff;
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, &color);

    batcher.textures[0] = white_texture;
    batcher.texture_count = 1;
    for (U32 i = 1; i < 32; i++) {
        batcher.textures[i] = 0;
    }

    glUseProgram(shader);
    I32 samplers[32] = {0};
    for (I32 i = 0; i < 32; i++) {
        samplers[i] = i;
    }
    glUniform1iv(glGetUniformLocation(shader, "textures"), 32, samplers);

    // Create vertex array
    glGenVertexArrays(1, &batcher.vertex_array);
    glBindVertexArray(batcher.vertex_array);

    // Configure vertex buffer
    glGenBuffers(1, &batcher.vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, batcher.vertex_buffer);

    glBufferData(GL_ARRAY_BUFFER, vertex_size * max_quads * 4, NULL, GL_DYNAMIC_DRAW);

    for (U32 i = 0; i < daCount(layout); i++) {
        glVertexAttribPointer(i, layout[i].size, GL_FLOAT, GL_FALSE, vertex_size, (const void *) layout[i].offset);
        glEnableVertexAttribArray(i);
    }

    // Configure element buffer
    glGenBuffers(1, &batcher.element_array);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, batcher.element_array);

    U32 indices[max_quads * 6];
    U32 offset = 0;
    for (U32 i = 0; i < max_quads * 6; i += 6) {
        indices[i + 0] = offset + 0;
        indices[i + 1] = offset + 1;
        indices[i + 2] = offset + 2;

        indices[i + 3] = offset + 2;
        indices[i + 4] = offset + 3;
        indices[i + 5] = offset + 1;

        offset += 4;
    }
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Unbind everything
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    return batcher;
}

void destroyBatcher(Batcher batcher)
{
    free(batcher.quad_buffer);

    glDeleteVertexArrays(1, &batcher.vertex_array);
    glDeleteBuffers(1, &batcher.vertex_buffer);
    glDeleteBuffers(1, &batcher.element_array);
    shaderDestroy(batcher.shader);

    glDeleteTextures(1, &batcher.textures[0]);
}

void flushBatcher(Batcher *batcher)
{
    // Bind textures
    for (U32 i = 0; i < batcher->texture_count; i++) {
        // glActiveTexture(GL_TEXTURE0 + i);
        // glBindTexture(GL_TEXTURE_2D, batcher->textures[i]);
        glBindTextureUnit(i, batcher->textures[i]);
    }

    // Draw call
    glUseProgram(batcher->shader);
    shaderUniformMat4(batcher->shader, "projection", *batcher->projection);

    glBindVertexArray(batcher->vertex_array);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, batcher->element_array);

    glDrawElements(GL_TRIANGLES, batcher->quad_count * 6, GL_UNSIGNED_INT, NULL);

    batcher->quad_count = 0;
    // Set to 1 to not delete blank texture at 0
    batcher->texture_count = 1;
}

void startBatcher(Batcher *batcher)
{
    batcher->quad_pointer = batcher->quad_buffer;
}

void endBatcher(Batcher *batcher)
{
    // Send vertex data to vertex buffer
    U64 size = (U8 *) batcher->quad_pointer - (U8 *) batcher->quad_buffer;
    glBindBuffer(GL_ARRAY_BUFFER, batcher->vertex_buffer);
    glBufferSubData(GL_ARRAY_BUFFER, 0, size, batcher->quad_buffer);
}
