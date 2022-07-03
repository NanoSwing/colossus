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
        8.0f,
        "Colossus test",
        true,
        hexRGB_1(0x0f1724)
    };
    initGraphics(g_config);

    Texture test = textureLoad("assets/textures/test.png");
    Texture circle = textureLoad("assets/textures/circle.png");
    SpriteSheet rainbow_sheet = spriteSheetLoad("assets/textures/rainbow_spritesheet.png", 8);

    // F32 rotation = 0;
    I32 frame = 0;

    F32 current_time = 0.0f;
    F32 last_time = getTime();
    F32 delta_time = 0.0f;

    F32 timer = 0.0f;

    while (graphicsRunning()) {
        graphicsLoopBegin();
        
        beginBatch();
        
        current_time = getTime();
        delta_time = (current_time - last_time);
        last_time = current_time;

        // Calculate fps
        const F32 update_rate = 4.0f;
        static F32 next_update = 0.0f;
        static I32 frame_count = 0;
        static I32 fps = 0;

        frame_count++;
        next_update += delta_time;
        if (next_update >= 1.0f / update_rate) {
            next_update = 0.0f;
            fps = frame_count * update_rate;
            frame_count = 0.0f;
        }
        logInfo("Delta time: '%f', FPS: '%d'", delta_time, fps);


        for (F32 y = -3; y <= 3; y += 0.2f) {
            for (F32 x = -3; x <= 3; x += 0.2f) {
                drawColor(vec2(x, y), vec2s(0.2f), 0, vec4((x + 3.0f) / 6.0f, (y + 3.0f) / 6.0f, 0.0f, 1.0f));
            }
        }

        F32 distance_between = 360.0f / 90.0f;
        F32 starting_angle = -360.0f + distance_between;
        for (F32 i = starting_angle; i <= 0; i += distance_between) {
            drawLineLength(vec2s(0.0f), 2.0f, i, 0.01f, vec4(hexRGBA_1(0xFFFFFF80)));
        }

        // drawTexture(vec2(0, 0), vec2s(1), 0, test);
        // drawColor(vec2(1, 1), vec2(0.25f, 1), 45, vec4(1, 0.5f, 0.5f, 1.0f));
        drawSpriteSheet(vec2s(0), vec2s(1), 0, rainbow_sheet, frame);

        timer += delta_time;
        if (timer >= 0.1f) {
            timer = 0.0f;
            frame++;
            if (frame > 7) {
                frame = 0;
            }
        }

        endBatch();
        flushBatch();

        graphicsLoopEnd();
    }

    textureDestroy(test);
    textureDestroy(circle);
    spriteSheetDestroy(rainbow_sheet);

    terminateGraphics();
    return 0;
}

// Square color     = 0xff8f1f
// Background color = 0x0f2422
