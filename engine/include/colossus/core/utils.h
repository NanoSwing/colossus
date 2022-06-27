#pragma once

#include "colossus/core/defs.h"

//
// Turn hex into usable color values
//

// 0 - 255
#define hexRGB_255(hex) \
    (F32) ((hex >> 8 * 2) & 0xFF), \
    (F32) ((hex >> 8 * 1) & 0xFF), \
    (F32) ((hex >> 8 * 0) & 0xFF)
#define hexRGBA_255(hex) \
    (F32) ((hex >> 8 * 3) & 0xFF), \
    (F32) ((hex >> 8 * 2) & 0xFF), \
    (F32) ((hex >> 8 * 1) & 0xFF), \
    (F32) ((hex >> 8 * 0) & 0xFF)

// 0 - 1
#define hexRGB_1(hex) \
    (F32) ((hex >> 8 * 2) & 0xFF) / (F32) 0xFF, \
    (F32) ((hex >> 8 * 1) & 0xFF) / (F32) 0xFF, \
    (F32) ((hex >> 8 * 0) & 0xFF) / (F32) 0xFF
#define hexRGBA_1(hex) \
    (F32) ((hex >> 8 * 3) & 0xFF) / (F32) 0xFF, \
    (F32) ((hex >> 8 * 2) & 0xFF) / (F32) 0xFF, \
    (F32) ((hex >> 8 * 1) & 0xFF) / (F32) 0xFF, \
    (F32) ((hex >> 8 * 0) & 0xFF) / (F32) 0xFF

#define clamp(value, min, max) value = value <= min ? min : value; value = value >= max ? max : value

#define TRUE_FALSE_UPPER(boolean) boolean == 1 ? "True" : "False" 
#define TRUE_FALSE_LOWER(boolean) boolean == 1 ? "true" : "false" 
