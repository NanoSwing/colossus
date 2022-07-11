#pragma once

#include "colossus/ecs/ecs.h"
#include "colossus/core/defs.h"
#include "colossus/core/math/vec4.h"
#include "colossus/core/math/vec2.h"
#include "colossus/graphics/textures.h"

/*
 * Sprite renderer component.
 */
typedef struct {
    /* Texture. */
    Texture texture;
    /* Color. */
    Vec4 color;
    /* Flip the texture horizontally. */
    B8 flip_horizontal;
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
 * Line point renderer component.
 */
typedef struct {
    /* Point a. */
    Vec2 a;
    /* Point b. */
    Vec2 b;
    /* Line thickness. */
    F32 thickness;
    /* Color. */
    Vec4 color;
} LinePointRenderer;
/*
 * Line point renderer component ID.
 */
extern I32 COMP_LINE_POINT_RENDERER;

/*
 * Line length renderer component.
 */
typedef struct {
    /* Origin of line. */
    Vec2 start;
    /* Line length. */
    F32 length;
    /* Angle in degrees rotating clockwise from pointing straight up. */
    F32 angle;
    /* Line thickness. */
    F32 thickness;
    /* Color. */
    Vec4 color;
} LineLengthRenderer;
/*
 * Line length renderer ID.
 */
extern I32 COMP_LINE_LENGTH_RENDERER;

/*
 * Wire quad renderer component.
 */
typedef struct {
    /* Line thickness. */
    F32 thickness;
    /* Color. */
    Vec4 color;
} WireQuadRenderer;
/*
 * Wire quad renderer component ID.
 */
extern I32 COMP_WIRE_QUAD_RENDERER;

/*
 * Add graphics addon to ecs.
 *
 * ecs - ECS.
 * system_group - System group ID.
 */
extern void ecsAddonGraphics(ECS *ecs, U32 system_group);
