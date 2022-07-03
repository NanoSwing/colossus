#pragma once

#include "colossus/ecs/ecs.h"
#include "colossus/graphics/graphics.h"

typedef struct {
    Texture texture;
    Vec4 color;
} SpriteRenderer;

extern I32 COMP_SPRITE_RENDERER;
extern void ecsAddonGraphics(ECS *ecs, U32 system_group);
