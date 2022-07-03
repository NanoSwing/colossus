#include "ecs_addons/internal_ecs_addons.h"
#include "colossus/resource_manager/resource_manager.h"

static void calculateDeltaTimeSystem(ECS *ecs)
{
    (void) ecs;

    static F32 current_time = 0.0f;
    static F32 last_time = 0.0f;
    static F32 delta_time = 0.0f;
    
    current_time = getTime();
    delta_time = (current_time - last_time);
    last_time = current_time;

    resourceSet("delta_time", delta_time);
}

I32 COMP_TRANSFORM = -1;
void ecsAddonCore(ECS *ecs, U32 system_group)
{
    COMP_TRANSFORM = ecsAddComponent(ecs, sizeof(Transform));
    ecsAddSystem(ecs, calculateDeltaTimeSystem, system_group);
}
