#include "colossus/core/utils.h"

#include <string.h>

/*
 * If the starting point is greater than the end point the item could not be found.
 *
 * Check if the current mid point is the value we're looking for.
 * 
 * Search either left or right side depending on result of comp_func
 * Use recursion to call itself with half of its initial searching range.
 */
I32 binarySearch(const void *arr, const void *key, I32 start, I32 end, U64 size, bs_comp_func comp_func)
{
    if (start > end) {
        return -1;
    }

    U32 mid = start + (end - start) / 2;

    I32 comp_result = comp_func(key, arr + mid * size);
    if (comp_result == 0) {
        return mid;
    } else if (comp_result > 0) {
        return binarySearch(arr, key, mid + 1, end, size, comp_func);
    } else {
        return binarySearch(arr, key, start, mid - 1, size, comp_func);
    }
}

/*
 * Return 0 if they match.
 * Return 1 when greater.
 * Return -1 when less than.
 * 
 * These return values are chosen to make string comparison work.
 */
I32 compInt(const void *_a, const void *_b)
{
    const I32 *a = _a;
    const I32 *b = _b;

    if (*a == *b) { return 0; }
    else if (*a > *b) { return 1; }
    else { return -1; }
}
/*
 * Just return the result of strcmp.
 * It'll return 0 if they match.
 * Lower than 0 it's less than.
 * Greater than 0 if it's greater than.
 */
I32 compStr(const void *_a, const void *_b)
{
    const char *a = _a;
    const char *b = _b;
    
    return strcmp(a, b);
}
