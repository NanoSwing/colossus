#include <stdio.h>

#include "colossus/colossus.h"
#include "colossus/graphics/graphics.h"
#include "colossus/core/logger.h"
#include "colossus/core/math/vec2.h"

#include <math.h>

I32 main(void)
{
    GraphicsConfig g_config = {
        1280,
        720,
        8.0f,
        "Colossus test",
        true,
        hexRGB_1(0x0f2422)
    };
    initGraphics(g_config);

    F32 rotation = 0;
    while (graphicsRunning()) {
        graphicsLoopBegin();
        
        beginBatch();
        
        for (F32 y = -3; y <= 3; y += 0.2f) {
            for (F32 x = -3; x <= 3; x += 0.2f) {
                drawQuad(vec2(x, y), vec2s(0.2f), rotation, vec3((x + 3.0f) / 6.0f, (y + 3.0f) / 6.0f, 0.0f));
            }
        }

        flushBatch();
        endBatch();

        graphicsLoopEnd();
    }

    terminateGraphics();
    return 0;
}

// Square color     = 0xff8f1f
// Background color = 0x0f2422
