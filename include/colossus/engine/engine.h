#pragma once

#include "colossus/core/defs.h"
#include "colossus/ecs/ecs.h"
#include "colossus/graphics/graphics.h"

/*
 * Global state structure.
 */
typedef struct {
    /* Time between two frames. */
    F32 delta_time;
    /* Seconds between fixed time steps. */
    F32 fixed_delta_time;
    /* Camera. */
    Camera *camera;
} GlobalState;
/*
 * Global state.
 */
extern GlobalState global;

/*
 * Opaque engien structure.
 */
typedef struct Engine Engine;

/*
 * System group.
 */
typedef enum {
    /* Updates a fixed amount of times per second at a fixed timestep. */
    SYS_FIXED_UPDATE,
    /* Runs before main update system group. */
    SYS_PRE_UPDATE,
    /* Main update system group. */
    SYS_UPDATE,
    /* Runs after main system group. */
    SYS_LATE_UPDATE,

    /* Amount of system groups. */
    SYS_GROUP_COUNT
} SystemGroup;

/*
 * Create an engine structure.
 *
 * width - Window width.
 * height - Window height.
 * title - Window title.
 * resizable - Is the window resizable.
 * pixels_per_unit - How many pixels one unit is.
 * max_entity_count - Max amount of entities in ECS.
 * ecs - Configured ECS from engine to be further configured by user.
 */
extern Engine *engineCreate(I32 width, I32 height, const char *title, B8 resizable, I32 max_entity_count, ECS **ecs);
/*
 * Configurations before engien is ready to use. Bakes ECS.
 *
 * engine - Engine.
 */
extern void engineSetup(Engine *engine);
/*
 * Starts the engine loop, running all ecs systems and graphics.
 *
 * engine - Engine.
 */
extern void engineStart(Engine *engine);
/*
 * Free all used memory and clean everything up.
 *
 * engine - Pointer to engine. Will be set to NULL.
 */
extern void engineDestroy(Engine **engine);
