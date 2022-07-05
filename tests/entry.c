#include <stdio.h>

#include "colossus/core/defs.h"

extern void testResourceManager(void);
extern void testBinarySearch(void);
extern void testMath(void);

I32 main(void)
{
    testResourceManager();
    printf("\n");
    testBinarySearch();
    printf("\n");
    testMath();

    return 0;
}
