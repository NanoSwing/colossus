#pragma once

#include "colossus/core/math/mat4.h"
#include "colossus/graphics/textures.h"

typedef unsigned int Shader;

extern Shader shaderCreateStr(const char *vertex_source, const char *fragment_source);
extern Shader shaderCreate(const char *vertex_path, const char *fragmnet_path);

extern void shaderDestroy(Shader shader);
extern void shaderUse(Shader shader);

extern void shaderUniformMat4(Shader shader, const char *name, Mat4 mat);
extern void shaderUniformIv(Shader shader, const char *name, I32 count, I32 *value);
extern void shaderUniformFv(Shader shader, const char *name, I32 count, F32 *value);
