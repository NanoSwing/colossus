#pragma once

#include "colossus/core/defs.h"
#include "colossus/core/math/mat4.h"

/*
 * Shader ID.
 */
typedef I32 Shader;

/*
 * Creates a shader.
 *
 * vertex_path - Path to vertex shader.
 * fragment_path - Path to fragment shader.
 * 
 * Returns shader ID if successful, returns -1 if not.
 */
extern Shader shaderCreate(const char *vertex_path, const char *fragment_path);
/*
 * Wrapper for OpenGL glDestroyProgram().
 *
 * shader - Shader ID.
 */
extern void shaderDestroy(Shader shader);

/*
 * Uploads a 4x4 matrix to a shader.
 *
 * shader - Shader ID.
 * name - Name of uniform.
 * mat - 4x4 matrix.
 */
extern void shaderUniformMat4(Shader shader, const char *name, Mat4 mat);
