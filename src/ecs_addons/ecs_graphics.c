#include "colossus/ecs_addons/graphics_ecs.h"

I32 COMP_SPRITE_RENDERER = -1;
I32 COMP_ANIMATION = -1;
I32 COMP_LINE_POINT_RENDERER = -1;
I32 COMP_LINE_LENGTH_RENDERER = -1;
I32 COMP_WIRE_QUAD_RENDERER = -1;

void ecsAddonGraphics(ECS *ecs, U32 system_group)
{
    (void) system_group;
    
    COMP_SPRITE_RENDERER = ecsAddComponent(ecs, sizeof(SpriteRenderer));
    COMP_ANIMATION = ecsAddComponent(ecs, sizeof(Animation));
    COMP_LINE_POINT_RENDERER = ecsAddComponent(ecs, sizeof(LinePointRenderer));
    COMP_LINE_LENGTH_RENDERER = ecsAddComponent(ecs, sizeof(LineLengthRenderer));
    COMP_WIRE_QUAD_RENDERER = ecsAddComponent(ecs, sizeof(WireQuadRenderer));
}
