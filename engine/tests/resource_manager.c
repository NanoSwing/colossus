#include "test.h"

#include "colossus/resman/resman.h"

void testResourceManager(void)
{
    resourceManagerInit();

    resourceSet("pi", 3.14f);

    {
        F32 *pi = resourceGet("pi");
        F32 expected = 3.14f;
        checkSuccess(pi, &expected, sizeof(F32), "Resource Manager - Set (Add)");
        checkSuccess(pi, &expected, sizeof(F32), "Resource Manager - Get");
    }

    {
        resourceSet("pi", 6.28f);
        F32 expected = 6.28f;
        F32 *pi = resourceGet("pi");
        checkSuccess(pi, &expected, sizeof(F32), "Resource Manager - Set (Update)");
    }

    {
        B8 success = true;
        resourceDelete("pi");
        F32 *pi = resourceGet("pi");
        if (pi == NULL) {
            checkSuccess(&success, &success, sizeof(F32), "Resource Manager - Delete");
        } else {
            checkSuccess(NULL, NULL, sizeof(F32), "Resource Manager - Delete");
        }
    }

    resourceManagerTerminate();
}
