#pragma once

#include "colossus/core/defs.h"

typedef U32 Texture;

extern Texture textureLoad(const char *path);
extern void textureDestroy(Texture texture);
