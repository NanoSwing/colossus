#include "colossus/ecs_addons/core_ecs.h"
#include "colossus/resource_manager/resource_manager.h"
#include "colossus/engine/engine.h"
#include "colossus/graphics/input.h"
#include "colossus/graphics/graphics.h"

static void calculateDeltaTimeSystem(ECS *ecs)
{
    (void) ecs;

    static F32 current_time = 0.0f;
    static F32 last_time = 0.0f;
    static F32 delta_time = 0.0f;

    // Give last_time an initial value so delta_time isn't super high at the start.    
    if (last_time == 0) {
        last_time = getTime();
    }

    current_time = getTime();
    delta_time = (current_time - last_time);
    last_time = current_time;

    global.delta_time = delta_time;
}

static void fullscreenSystem(ECS *ecs)
{
    (void) ecs;
    
    if (keyDown(KEY_F11)) {
        Graphics *graphics = *(Graphics **) resourceGet("graphics");
        graphicsToggleFullscreen(graphics);
    }
}

I32 COMP_TRANSFORM = -1;
void ecsAddonCore(ECS *ecs, U32 system_group)
{
    COMP_TRANSFORM = ecsAddComponent(ecs, sizeof(Transform));
    ecsAddSystem(ecs, calculateDeltaTimeSystem, system_group);
    ecsAddSystem(ecs, fullscreenSystem, system_group);
}
