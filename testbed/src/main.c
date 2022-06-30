#include <stdio.h>

#include "colossus/colossus.h"
#include "colossus/graphics/graphics.h"
#include "colossus/core/logger.h"

I32 main(void)
{
    GraphicsConfig g_config = {
        1280,
        720,
        "Colossus test",
        true,
        hexRGB_1(0x0f2422)
    };
    initGraphics(g_config);

    while (graphicsRunning()) {
        graphicsLoop();
    }

    terminateGraphics();
    return 0;
}

// Square color     = 0xff8f1f
// Background color = 0x0f2422
