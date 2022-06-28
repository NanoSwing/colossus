#include <stdio.h>

#include "colossus/core/defs.h"

extern void testResourceManager(void);
extern void testBinarySearch(void);

I32 main(void)
{
    testResourceManager();
    printf("\n");
    testBinarySearch();

    return 0;
}
