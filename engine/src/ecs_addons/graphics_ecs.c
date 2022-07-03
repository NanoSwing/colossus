#include "ecs_addons/internal_ecs_addons.h"
#include "graphics/internal_graphics.h"

I32 COMP_SPRITE_RENDERER = -1;

static void renderingSystem(ECS *ecs)
{
    graphicsLoopBegin();

    const Component *sprite_renderer_component = ecsGetComponent(ecs, COMP_SPRITE_RENDERER);
    SpriteRenderer *sr = sprite_renderer_component->storage;
    Transform *transforms = ecsGetComponent(ecs, COMP_TRANSFORM)->storage;

    beginBatch();
    for (U32 i = 0; i < daCount(sprite_renderer_component->entities); i++) {
        // Does entity have a transform?
        Entity ent = sprite_renderer_component->entities[i];
        if (!entityHasComponent(ent, COMP_TRANSFORM)) {
            continue;
        }

        I32 e = ent.ID;

        drawQuad(transforms[e].position, transforms[e].scale, transforms[e].rotation, sr[e].color, sr[e].texture, 1, 0);
    }
    endBatch();
    flushBatch();

    graphicsLoopEnd();
}

void ecsAddonGraphics(ECS *ecs, U32 system_group)
{
    COMP_SPRITE_RENDERER = ecsAddComponent(ecs, sizeof(SpriteRenderer));
    ecsAddSystem(ecs, renderingSystem, system_group);
}

