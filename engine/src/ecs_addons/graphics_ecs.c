#include "ecs_addons/internal_ecs_addons.h"
#include "graphics/internal_graphics.h"

I32 COMP_SPRITE_RENDERER = -1;
I32 COMP_ANIMATION = -1;

static void renderingSystem(ECS *ecs)
{
    graphicsLoopBegin();

    const Component *sprite_renderer_component = ecsGetComponent(ecs, COMP_SPRITE_RENDERER);
    SpriteRenderer *sr = sprite_renderer_component->storage;
    Transform *transforms = ecsGetComponent(ecs, COMP_TRANSFORM)->storage;
    Animation *animations = ecsGetComponent(ecs, COMP_ANIMATION)->storage;

    beginBatch();
    for (U32 i = 0; i < daCount(sprite_renderer_component->entities); i++) {
        // Does entity have a transform?
        Entity ent = sprite_renderer_component->entities[i];
        if (!entityHasComponent(ent, COMP_TRANSFORM)) {
            continue;
        }


        I32 e = ent.id;

        I32 frame_count = 1;
        I32 frame = 0;
        if (entityHasComponent(ent, COMP_ANIMATION)) {
            frame_count = animations[e].frame_count;
            frame = animations[e].frame;
        }

        drawQuad(transforms[e].position, transforms[e].scale, transforms[e].rotation, sr[e].color, sr[e].texture, frame_count, frame);
    }
    endBatch();
    flushBatch();

    graphicsLoopEnd();
}

void ecsAddonGraphics(ECS *ecs, U32 system_group)
{
    COMP_SPRITE_RENDERER = ecsAddComponent(ecs, sizeof(SpriteRenderer));
    COMP_ANIMATION = ecsAddComponent(ecs, sizeof(Animation));
    ecsAddSystem(ecs, renderingSystem, system_group);
}

