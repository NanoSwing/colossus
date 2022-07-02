#pragma once

#include "colossus/core/defs.h"
#include "colossus/core/math/mat4.h"

typedef U32 Shader;

extern Shader shaderCreate(const char *vertex_path, const char *fragment_path);
extern void shaderDestroy(Shader shader);

extern void shaderUniformMat4(Shader shader, const char *name, Mat4 mat);
