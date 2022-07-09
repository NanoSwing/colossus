#include "colossus/graphics/shaders.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

#include <glad/glad.h>

Shader shaderCreateStr(const char *vertex_source, const char *fragment_source)
{
    int success;
    char info_log[512];

    // Vertex shader
    unsigned int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_source, NULL);
    glCompileShader(vertex_shader);
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
    // Error handling
    if (!success) {
        glGetShaderInfoLog(vertex_shader, 512, NULL, info_log);
        printf("Vertex shader compilation error: '%s'\n", info_log);
    }

    // Fragment shader
    unsigned int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_source, NULL);
    glCompileShader(fragment_shader);
    // Error handling
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragment_shader, 512, NULL, info_log);
        printf("Fragment shader compilation error: '%s'\n", info_log);
    }

    // Program
    Shader program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);
    // Error handling
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program, 512, NULL, info_log);
        printf("Shader linking error: '%s'\n", info_log);
    }

    return program;
}

static char *readFile(const char *path)
{
    // Open file
    FILE *fp = fopen(path, "rb");
    if (fp == NULL) {
        printf("Unable to open file: '%s'\n", path);
        return NULL;
    }

    // Get length
    fseek(fp, 0, SEEK_END);
    int length = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    // Read
    char *buffer = malloc(length + 1);
    fread(buffer, length, 1, fp);
    buffer[length] = '\0';
    
    return buffer;
}

Shader shaderCreate(const char *vertex_path, const char *fragmnet_path)
{
    char *vertex_source = readFile(vertex_path);
    char *fragment_source = readFile(fragmnet_path);

    Shader program = shaderCreateStr(vertex_source, fragment_source);

    free(vertex_source);
    free(fragment_source);

    return program;
}

void shaderDestroy(Shader shader)
{
    glDeleteProgram(shader);
}

void shaderUse(Shader shader)
{
    glUseProgram(shader);
}

void shaderUniformMat4(Shader shader, const char *name, Mat4 mat)
{
    I32 location = glGetUniformLocation(shader, name);
    glUniformMatrix4fv(location, 1, false, &mat.a.x);
}
void shaderUniformIv(Shader shader, const char *name, I32 count, I32 *value)
{
    I32 location = glGetUniformLocation(shader, name);
    glUniform1iv(location, count, value);
}

void shaderUniformFv(Shader shader, const char *name, I32 count, F32 *value)
{
    I32 location = glGetUniformLocation(shader, name);
    glUniform1fv(location, count, value);
}
