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

I32 COMP_ANIMATION_CONTROLLER = -1;
typedef struct {
    F32 timer;
} AnimationController;
void animator(ECS *ecs)
{
    F32 delta_time = *(F32 *) resourceGet("delta_time");

    const Component *controller_component = ecsGetComponent(ecs, COMP_ANIMATION_CONTROLLER);
    AnimationController *controllers = controller_component->storage;
    Animation *anims = ecsGetComponent(ecs, COMP_ANIMATION)->storage;
    for (U32 i = 0; i < daCount(controller_component->entities); i++) {
        Entity ent = controller_component->entities[i];
        if (!entityHasComponent(ent, COMP_ANIMATION)) {
            continue;
        }
        
        I32 e = ent.id;

        controllers[e].timer += delta_time;
        if (controllers[e].timer >= 0.1f) {
            controllers[e].timer = 0.0f;
            anims[e].frame++;
            if (anims[e].frame == 8) {
                anims[e].frame = 0;
            }
        }
    }
}

I32 main(void)
{
    GraphicsConfig g_config = {
        1280,
        720,
        68.0f,
        "Colossus test",
        true,
        vec3(hexRGB_1(0x0f1724))
    };
    graphicsInit(g_config);
    resourceManagerInit();

    ECS *ecs = ecsCreate(1024 * 16, 1);
    ecsAddonCore(ecs, 0);
    ecsAddonGraphics(ecs, 0);

    COMP_ANIMATION_CONTROLLER = ecsAddComponent(ecs, sizeof(AnimationController));

    ecsAddSystem(ecs, calculateFps, 0);
    ecsAddSystem(ecs, animator, 0);

    ecsBake(ecs);

    // Texture tex = textureLoad("assets/textures/test.png", MIN_MAG_NEAREST);
    Texture sheet = textureLoad("assets/textures/rainbow_spritesheet.png", MIN_MAG_NEAREST);

    I32 entity_count = 0;
    for (F32 y = -32.0f; y < 32.0f; y += 0.5f) {
        for (F32 x = -32.0f; x < 32.0f; x += 0.5f) {
            Entity test = ecsCreateEntity(ecs);
            entityAddComponent(test, COMP_TRANSFORM);
            entityAddComponent(test, COMP_SPRITE_RENDERER);
            entityAddComponent(test, COMP_ANIMATION);
            entityAddComponent(test, COMP_ANIMATION_CONTROLLER);
            Transform *trans = entityGetComponent(test, COMP_TRANSFORM);
            trans->position = vec2(x + 0.25f, y + 0.25f);
            trans->scale = vec2s(0.4f);
            trans->rotation = 0.0f;
            SpriteRenderer *sr = entityGetComponent(test, COMP_SPRITE_RENDERER);
            sr->texture = sheet;
            sr->color = vec4s(1.0f);
            Animation *anim = entityGetComponent(test, COMP_ANIMATION);
            anim->frame = 0;
            anim->frame_count = 8;
            entity_count++;
        }
    }

    while (graphicsRunning()) {
        ecsRun(ecs, 0);
    }

    textureDestroy(sheet);

    resourceManagerTerminate();
    graphicsTerminate();
    return 0;
}
