#include "graphics/shader.h"
#include "colossus/core/logger.h"

#include <stdio.h>
#include <malloc.h>

#include <glad/glad.h>

static char *readFile(const char *path)
{
    FILE *fs = fopen(path, "rb");
    if (fs == NULL) {
        logError("Unable to open '%s'!", path);
        return NULL;
    }

    U64 len = 0;
    fseek(fs, 0, SEEK_END);
    len = ftell(fs);
    fseek(fs, 0, SEEK_SET);

    char *buffer = malloc(len + 1);
    
    fread(buffer, 1, len, fs);
    buffer[len] = '\0';

    return buffer;
}

Shader shaderCreate(const char *vertex_path, const char *fragment_path)
{
    Shader shader = glCreateProgram();

    // Error handling
    I32 success;
    char info_log[512];

    U32 vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    const char *vertex_source = readFile(vertex_path);
    glShaderSource(vertex_shader, 1, &vertex_source, NULL);
    free((char *) vertex_source);
    glCompileShader(vertex_shader);
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertex_shader, 512, NULL, info_log);
        logWarn("Vertex shader compilation failed: '%s'", info_log);
    }

    U32 fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    const char *fragment_source = readFile(fragment_path);
    glShaderSource(fragment_shader, 1, &fragment_source, NULL);
    free((char *) fragment_source);
    glCompileShader(fragment_shader);
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragment_shader, 512, NULL, info_log);
        logWarn("Fragment shader compilation failed: '%s'", info_log);
    }

    glAttachShader(shader, vertex_shader);
    glAttachShader(shader, fragment_shader);
    glLinkProgram(shader);
    glGetProgramiv(shader, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shader, 512, NULL, info_log);
        logWarn("Shader linking failed: '%s'", info_log);
    }

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    return shader;
}

void shaderDestroy(Shader shader)
{
    glDeleteProgram(shader);
}

void shaderUniformMat4(Shader shader, const char *name, Mat4 mat)
{
    I32 location = glGetUniformLocation(shader, name);
    glUniformMatrix4fv(location, 1, false, &mat.a.x);
}
