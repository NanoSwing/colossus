#include <stdio.h>

#include "colossus/colossus.h"
#include "colossus/graphics/graphics.h"
#include "colossus/graphics/texture.h"

#include <math.h>

I32 main(void)
{
    GraphicsConfig g_config = {
        1280,
        720,
        3.0f,
        "Colossus test",
        true,
        hexRGB_1(0x0f1724)
    };
    initGraphics(g_config);

    Texture test = textureLoad("assets/textures/test.png");
    Texture circle = textureLoad("assets/textures/circle.png");

    // F32 rotation = 0;
    while (graphicsRunning()) {
        graphicsLoopBegin();
        
        beginBatch();
        
        // for (F32 y = -3; y <= 3; y += 0.2f) {
        //     for (F32 x = -3; x <= 3; x += 0.2f) {
        //         drawQuad(vec2(x, y), vec2s(0.2f), rotation, vec4((x + 3.0f) / 6.0f, (y + 3.0f) / 6.0f, 0.0f, 1.0f), test);
        //     }
        // }
        drawQuad(vec2(-1, 0), vec2s(1), 0, vec4s(1), test);
        drawQuad(vec2(1, 0), vec2s(1), 0, vec4(1, 0.5f, 0.5f, 1.0f), circle);

        endBatch();
        flushBatch();

        graphicsLoopEnd();
    }

    textureDestroy(test);
    textureDestroy(circle);

    terminateGraphics();
    return 0;
}

// Square color     = 0xff8f1f
// Background color = 0x0f2422
