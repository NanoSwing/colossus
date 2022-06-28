#include "colossus/core/utils.h"
#include "test.h"

void testBinarySearch(void)
{
    I32 array[] = { 2, 3, 5, 7, 9, 21, 29, 32 };
    U32 count = sizeof(array) / sizeof(array[0]);

    {
        I32 key = 2;
        I32 result = binarySearch(array, &key, 0, count, sizeof(I32), compInt);
        I32 expected = 0;
        checkSuccess(&result, &expected, sizeof(I32), "Binary Search - First index");
    }

    {
        I32 key = 9;
        I32 result = binarySearch(array, &key, 0, count, sizeof(I32), compInt);
        I32 expected = 4;
        checkSuccess(&result, &expected, sizeof(I32), "Binary Search - Middle index");
    }

    {
        I32 key = 32;
        I32 result = binarySearch(array, &key, 0, count, sizeof(I32), compInt);
        I32 expected = 7;
        checkSuccess(&result, &expected, sizeof(I32), "Binary Search - Last index");
    }
}
