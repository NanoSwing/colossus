#pragma once

#include "colossus/core/defs.h"
#include "colossus/core/math/mat4.h"
#include "colossus/graphics/textures.h"

/*
 * Shader program ID.
 */
typedef I32 Shader;

/*
 * Create a shader program from strings.
 *
 * vertex_source - Vertex shader source code.
 * fragment_source - Fragment shader source code.
 * 
 * Returns the shader program. Returns -1 if error occured.
 */
extern Shader shaderCreateStr(const char *vertex_source, const char *fragment_source);
/*
 * Create a shader program from files.
 *
 * vertex_source - Vertex shader file path.
 * fragment_source - Fragment shader file path.
 * 
 * Returns the shader program. Returns -1 if error occured.
 */
extern Shader shaderCreate(const char *vertex_path, const char *fragmnet_path);

/*
 * Destroy shader.
 *
 * shader - Shader program.
 */
extern void shaderDestroy(Shader shader);
/*
 * Use shader.
 *
 * shader - Shader program.
 */
extern void shaderUse(Shader shader);

/*
 * Upload a 4x4 matrix uniform to shader.
 * Use the shader before uploading uniforms.
 *
 * shader - Shader program.
 * name - Uniform name.
 * mat - 4x4 matrix.
 */
extern void shaderUniformMat4(Shader shader, const char *name, Mat4 mat);
/*
 * Upload an int array uniform to shader. Can also be used to send a single int.
 * Use the shader before uploading uniforms.
 *
 * shader - Shader program.
 * name - Uniform name.
 * value - Int array.
 */
extern void shaderUniformIv(Shader shader, const char *name, I32 count, I32 *value);
/*
 * Upload an Float array uniform to shader. Can also be used to send a single float.
 * Use the shader before uploading uniforms.
 *
 * shader - Shader program.
 * name - Uniform name.
 * value - Float array.
 */
extern void shaderUniformFv(Shader shader, const char *name, I32 count, F32 *value);
