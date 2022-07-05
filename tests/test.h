#pragma once

#include <string.h>
#include <stdio.h>

#include "colossus/core/defs.h"

inline static void checkSuccess(const void *a, const void *b, U64 size, const char *message)
{
    U32 success = 0;
    if (!(a == NULL || b == NULL)) {
        success = !memcmp(a, b, size);
    }

    if (success) {
        printf("\033[0;32m%s succeeded.\033[0;0m\n", message);
    } else {
        printf("\033[0;31m%s failed.\033[0;0m\n", message);
    }
}
