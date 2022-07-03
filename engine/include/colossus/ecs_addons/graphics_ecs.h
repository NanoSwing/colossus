#pragma once

#include "colossus/ecs/ecs.h"
#include "colossus/graphics/graphics.h"

/*
 * Sprite renderer component.
 */
typedef struct {
    /* Texture. */
    Texture texture;
    /* Color. */
    Vec4 color;
} SpriteRenderer;
/* Component ID of the sprite renderer component. */
extern I32 COMP_SPRITE_RENDERER;

/*
 * Adds graphics components and systems.
 *
 * ecs - ECS.
 * system_group - System group to add graphics systems to.
 */
extern void ecsAddonGraphics(ECS *ecs, U32 system_group);
