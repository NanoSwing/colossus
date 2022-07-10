#pragma once

#include "colossus/ecs/ecs.h"
#include "colossus/core/defs.h"
#include "colossus/core/math/vec4.h"
#include "colossus/graphics/textures.h"

/*
 * Sprite renderer component.
 */
typedef struct {
    /* Texture. */
    Texture texture;
    /* Color. */
    Vec4 color;
    /* Z layer specifing what objects should render on top of others. */
    I32 z_index;
} SpriteRenderer;
/*
 * Sprite renderer component ID.
 */
extern I32 COMP_SPRITE_RENDERER;

/*
 * Animation component.
 */
typedef struct {
    /* Amount of frames in spritesheet. */
    I32 frame_count;
    /* Current frame rendered. */
    I32 frame;
} Animation;
/*
 * Animation component ID.
 */
extern I32 COMP_ANIMATION;

/*
 * Add graphics addon to ecs.
 *
 * ecs - ECS.
 * system_group - System group ID.
 */
extern void ecsAddonGraphics(ECS *ecs, U32 system_group);
