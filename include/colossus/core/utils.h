#pragma once

#include "colossus/core/defs.h"

/*
 * Converts a hex number to three values between 0 - 255. Representing red, green and blue.
 *
 * hex - Hex vaule, ex. 0xff0000 (red)
 */
#define hexRGB_255(hex) \
    (F32) ((hex >> 8 * 2) & 0xFF), \
    (F32) ((hex >> 8 * 1) & 0xFF), \
    (F32) ((hex >> 8 * 0) & 0xFF)
/*
 * Converts a hex number to four values between 0 - 255. Representing red, green, blue and alpha.
 *
 * hex - Hex vaule, ex. 0xff000080 (red with half opacity)
 */
#define hexRGBA_255(hex) \
    (F32) ((hex >> 8 * 3) & 0xFF), \
    (F32) ((hex >> 8 * 2) & 0xFF), \
    (F32) ((hex >> 8 * 1) & 0xFF), \
    (F32) ((hex >> 8 * 0) & 0xFF)

/*
 * Converts a hex number to four values between 0 - 1. Representing red, green, blue and alpha.
 *
 * hex - Hex vaule, ex. 0xff000080 (red with half opacity)
 */
#define hexRGB_1(hex) \
    (F32) ((hex >> 8 * 2) & 0xFF) / (F32) 0xFF, \
    (F32) ((hex >> 8 * 1) & 0xFF) / (F32) 0xFF, \
    (F32) ((hex >> 8 * 0) & 0xFF) / (F32) 0xFF
/*
 * Converts a hex number to four values between 0 - 1. Representing red, green, blue and alpha.
 *
 * hex - Hex vaule, ex. 0xff000080 (red with half opacity)
 */
#define hexRGBA_1(hex) \
    (F32) ((hex >> 8 * 3) & 0xFF) / (F32) 0xFF, \
    (F32) ((hex >> 8 * 2) & 0xFF) / (F32) 0xFF, \
    (F32) ((hex >> 8 * 1) & 0xFF) / (F32) 0xFF, \
    (F32) ((hex >> 8 * 0) & 0xFF) / (F32) 0xFF

/*
 * Clamp a value between min and max.
 *
 * value - Value to clamp.
 * min - Lower bound.
 * max - Upper bound.
 */
#define clamp(value, min, max) value = value <= min ? min : value; value = value >= max ? max : value

/*
 * Linearly interpolate between a and b.
 *
 * a - Starting value.
 * b - Target value.
 * t - Controlls where along the interpolation we are.
 */
#define lerp(a, b, t) a + (b - a) * t

#define TRUE_FALSE_UPPER(boolean) boolean == 1 ? "True" : "False" 
#define TRUE_FALSE_LOWER(boolean) boolean == 1 ? "true" : "false" 

/*
 * A function comparing two objects.
 * Used to tell binarySearch what object is greater in value.
 */
typedef I32 (*bs_comp_func)(const void *_a, const void *_b);
/*
 * Search a sorted array with devide and conquer method.
 * 
 * arr - Array.
 * key - Key to be found.
 * start - What index the search begins in the array.
 * end - What index the search ends in the array.
 * size - Size of the array type.
 * comp_func - Function comparing two objects determening which is greater in value.
 * 
 * Returns the index of the searched value. If not found, returns -1.
 */
extern I32 binarySearch(const void *arr, const void *key, I32 start, I32 end, U64 size, bs_comp_func comp_func);

/*
 * Compare functions
 */

/*
 * Compare two ints.
 * Used when sorting and searching an int array.
 */
extern I32 compInt(const void *_a, const void *_b);
/*
 * Compare two strings.
 * Used when sorting and searching an int array.
 */
extern I32 compStr(const void *_a, const void *_b);

/*
 * Convert degrees into radians.
 */
#define rad(degrees) degrees *  0.017453
/*
 * Convert radians into degrees.
 */
#define deg(radians) radians * 57.295780

/*
 * Gets time with a high resolution clock.
 */
extern F64 getTime(void);
