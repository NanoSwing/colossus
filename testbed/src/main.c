#include <stdio.h>

#include "colossus/colossus.h"

#include "colossus/graphics/graphics.h"
#include "colossus/graphics/texture.h"

#include "colossus/ecs_addons/core_ecs.h"
#include "colossus/ecs_addons/graphics_ecs.h"

#include <math.h>

void calculateFps(ECS *ecs)
{
    (void) ecs;

    const F32 update_rate = 4.0f;
    static F32 next_update = 0.0f;
    static I32 frame_count = 0;
    static I32 fps = 0;

    F32 delta_time = *(F32 *) resourceGet("delta_time");

    frame_count++;
    next_update += delta_time;
    if (next_update >= 1.0f / update_rate) {
        next_update = 0.0f;
        fps = frame_count * update_rate;
        frame_count = 0.0f;
    }

    logInfo("Delta time: '%f', FPS: '%d'", delta_time, fps);
}

I32 main(void)
{
    GraphicsConfig g_config = {
        1280,
        720,
        5.0f,
        "Colossus test",
        true,
        hexRGB_1(0x0f1724)
    };
    initGraphics(g_config);
    resourceManagerInit();

    ECS *ecs = ecsCreate(1024, 1);
    ecsAddonCore(ecs, 0);
    ecsAddonGraphics(ecs, 0);

    ecsAddSystem(ecs, calculateFps, 0);

    ecsBake(ecs);

    Texture tex = textureLoad("assets/textures/test.png");

    Entity test = ecsCreateEntity(ecs);
    entityAddComponent(test, COMP_TRANSFORM);
    entityAddComponent(test, COMP_SPRITE_RENDERER);
    Transform *trans = entityGetComponent(test, COMP_TRANSFORM);
    trans->position = vec2s(0.0f);
    trans->scale = vec2s(1.0f);
    trans->rotation = 0.0f;
    SpriteRenderer *sr = entityGetComponent(test, COMP_SPRITE_RENDERER);
    sr->texture = tex;
    sr->color = vec4s(1.0f);

    while (graphicsRunning()) {
        ecsRun(ecs, 0);
    }

    resourceManagerTerminate();
    terminateGraphics();
    return 0;
}
