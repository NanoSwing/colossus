#include <stdio.h>

#include "colossus/colossus.h"

I32 main(void)
{
    resourceManagerInit();

    // Add new resource
    resourceSet("pi", 3.14f);
    // Get the resoruce
    printf("%f\n", *(F32 *) resourceGet("pi"));
    
    // Update value
    resourceSet("pi", 6.28f);
    // Get the updated resource
    printf("%f\n", *(F32 *) resourceGet("pi"));

    // Delete resource
    resourceDelete("pi");
    // Print the pointer address returned by resourceGet()
    printf("%p\n", resourceGet("pi"));

    resourceManagerTerminate();
    return 0;
}
