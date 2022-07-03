#include "graphics/shader.h"
#include "colossus/core/logger.h"

#include <stdio.h>
#include <malloc.h>

#include <glad/glad.h>

/*
 * Read a file.
 *
 * path - Path to file.
 * 
 * Returns a char buffer which needs to be freed when done using. Returns NULL if it fails.
 */
static char *readFile(const char *path)
{
    // Open file
    FILE *fs = fopen(path, "rb");
    if (fs == NULL) {
        logError("Unable to open '%s'!", path);
        return NULL;
    }

    // Get length of file
    U64 len = 0;
    fseek(fs, 0, SEEK_END);
    len = ftell(fs);
    fseek(fs, 0, SEEK_SET);

    
    // Read file
    char *buffer = malloc(len + 1);
    fread(buffer, 1, len, fs);
    // Add a null terminator at the end of the buffer to get rid of random characters at the end.
    buffer[len] = '\0';

    return buffer;
}

/*
 * Create vertex shader.
 * Create fragment shader.
 * Create program.
 * Link program with vertex and fragment shaders.
 */
Shader shaderCreate(const char *vertex_path, const char *fragment_path)
{
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
        return -1;
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
        return -1;
    }

    Shader shader = glCreateProgram();
    glAttachShader(shader, vertex_shader);
    glAttachShader(shader, fragment_shader);
    glLinkProgram(shader);
    glGetProgramiv(shader, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shader, 512, NULL, info_log);
        logWarn("Shader linking failed: '%s'", info_log);
        glDeleteProgram(shader);
        return -1;
    }

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    return shader;
}

/*
 * Delete the program.
 */
void shaderDestroy(Shader shader)
{
    glDeleteProgram(shader);
}

/*
 * Send 4x4 matrix uniform.
 */
void shaderUniformMat4(Shader shader, const char *name, Mat4 mat)
{
    I32 location = glGetUniformLocation(shader, name);
    glUniformMatrix4fv(location, 1, false, &mat.a.x);
}
