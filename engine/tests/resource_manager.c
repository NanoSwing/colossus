#include "test.h"

#include "colossus/resman/resman.h"

void testResourceManager(void)
{
    resourceManagerInit();

    resourceAdd(3.14f, "pi");

    F32 *pi = resourceGet("pi");
    F32 expected = 3.14f;
    checkSuccess(pi, &expected, sizeof(F32), "Resource Manager - Get");

    resourceUpdate(6.28f, "pi");
    expected = 6.28;
    pi = resourceGet("pi");
    checkSuccess(pi, &expected, sizeof(F32), "Resource Manager - Update");

    resourceDelete("pi");
    pi = resourceGet("pi");
    if (pi == NULL) {
        checkSuccess(&expected, &expected, sizeof(F32), "Resource Manager - Delete");
    } else {
        checkSuccess(NULL, NULL, sizeof(F32), "Resource Manager - Delete");
    }

    resourceManagerTerminate();
}
