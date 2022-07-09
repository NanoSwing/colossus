#pragma once

#include "colossus/core/defs.h"

typedef struct {
    I32 id;
} EBO;

extern EBO eboCreate(const I32 *indices, I32 index_count);
extern void eboDestroy(EBO ebo);

extern void eboBind(EBO ebo);
extern void eboUnbind(void);
