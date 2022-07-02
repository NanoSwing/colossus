#include "colossus/core/math/vec2.h"
#include "test.h"

void testMath(void)
{
    Vec2 result = vec2Normalize(vec2s(1));
    Vec2 expected = vec2s(0.7071f);
    checkSuccess(&result, &expected, sizeof(Vec2), "Math - Vec2 normalize");
}
