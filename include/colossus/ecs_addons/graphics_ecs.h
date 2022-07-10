#pragma once

#include "colossus/ecs/ecs.h"
#include "colossus/core/defs.h"
#include "colossus/core/math/vec4.h"
#include "colossus/graphics/textures.h"

typedef struct {
    Texture texture;
    Vec4 color;
} SpriteRenderer;
extern I32 COMP_SPRITE_RENDERER;

typedef struct {
    I32 frame_count;
    I32 frame;
} Animation;
extern I32 COMP_ANIMATION;

extern void ecsAddonGraphics(ECS *ecs, U32 system_group);
