#include <stdio.h>

#include "colossus/colossus.h"

#include <math.h>

void calculateFps(ECS *ecs)
{
    (void) ecs;

    const F32 update_rate = 4.0f;
    static F32 next_update = 0.0f;
    static I32 frame_count = 0;
    static I32 fps = 0;

    frame_count++;
    next_update += global.delta_time;
    if (next_update >= 1.0f / update_rate) {
        next_update = 0.0f;
        fps = frame_count * update_rate;
        frame_count = 0.0f;
        logInfo("Delta time: '%f', FPS: '%d'", global.delta_time, fps);
    }
}

I32 COMP_ANIMATION_CONTROLLER = -1;
typedef struct {
    F32 timer;
} AnimationController;
void animator(ECS *ecs)
{
    const Component *controller_component = ecsGetComponent(ecs, COMP_ANIMATION_CONTROLLER);
    AnimationController *controllers = controller_component->storage;
    Animation *anims = ecsGetComponent(ecs, COMP_ANIMATION)->storage;
    for (U32 i = 0; i < daCount(controller_component->entities); i++) {
        Entity ent = controller_component->entities[i];
        if (!entityHasComponent(ent, COMP_ANIMATION)) {
            continue;
        }
        
        I32 e = ent.id;

        controllers[e].timer += global.delta_time;
        if (controllers[e].timer >= 0.1f) {
            controllers[e].timer = 0.0f;
            anims[e].frame++;
            if (anims[e].frame == 8) {
                anims[e].frame = 0;
            }
        }
    }
}

I32 COMP_ROTATOR = -1;
typedef struct {
    F32 speed;
} Rotator;
void rotate(ECS *ecs)
{
    const Component *comp = ecsGetComponent(ecs, COMP_ROTATOR);
    Rotator *rotators = comp->storage;
    Transform *transforms = ecsGetComponent(ecs, COMP_TRANSFORM)->storage;

    for (U32 i = 0; i < daCount(comp->entities); i++) {
        Entity ent = comp->entities[i];
        if (!entityHasComponent(ent, COMP_TRANSFORM)) {
            continue;;
        }
        I32 e = ent.id;

        transforms[e].rotation += rotators[e].speed * global.delta_time;
        // drawLineLength(transforms[e].position, 0.5f, transforms[e].rotation, 0.05f, vec4(hexRGBA_1(0xFFFFFFFF)));
    }
}

I32 main(void)
{
    GraphicsConfig g_config = {
        1280,
        720,
        35.0f,
        "Colossus test",
        true,
        vec3(hexRGB_1(0x0f1724))
    };

    ColossusConfig c_config = {
        .graphics_config = g_config,
        .max_entities = 1024
    };

    ECS *ecs;
    colossusInit(c_config, &ecs);

    COMP_ANIMATION_CONTROLLER = ecsAddComponent(ecs, sizeof(AnimationController));
    COMP_ROTATOR = ecsAddComponent(ecs, sizeof(Rotator));

    ecsAddSystem(ecs, calculateFps, SYS_UPDATE);
    ecsAddSystem(ecs, animator, SYS_UPDATE);
    ecsAddSystem(ecs, rotate, SYS_UPDATE);

    colossusSetup(ecs);

    Texture sheet = textureLoad("assets/textures/rainbow_spritesheet.png", MIN_MAG_NEAREST);

    Entity *entity_pool = daCreate(sizeof(Entity));
    for (I32 i = 0; i < 1024; i++) {
        daPush(entity_pool, ecsCreateEntity(ecs));
    }
    Heap *tile_heap = heapCreate(sizeof(Entity), 1024, entity_pool, false);
    daDestroy(entity_pool);

    for (F32 y = -16.0f; y < 16.0f; y += 1.0f) {
        for (F32 x = -16.0f; x < 16.0f; x += 1.0f) {
            Entity test = NULL_ENTITY;
            heapGet(tile_heap, &test);
            entityDestroy(test);
            
            entityAddComponent(test, COMP_TRANSFORM, ((Transform) {.position = vec2(x + 0.5f, y + 0.5f), .rotation = 0.0f, .scale = vec2s(0.9f)}));
            entityAddComponent(test, COMP_SPRITE_RENDERER, ((SpriteRenderer) {.texture = sheet, .color = vec4(hexRGBA_1(0xffffffff))}));
            entityAddComponent(test, COMP_ANIMATION, ((Animation) {.frame = (I32) (x + y) % 8, .frame_count = 8}));
            entityAddComponent(test, COMP_ANIMATION_CONTROLLER, NULL);
            entityAddComponent(test, COMP_ROTATOR, ((Rotator) {.speed = (x + y) * 5.0f}));
        }
    }

    colossusStart(ecs);

    colossusTerminate(&ecs);
}
