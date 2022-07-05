#include "colossus/engine/engine.h"
#include "colossus/resource_manager/resource_manager.h"
#include "colossus/ecs_addons/core_ecs.h"
#include "colossus/ecs_addons/graphics_ecs.h"
#include "graphics/internal_graphics.h"

ColossusGlobal global = {0};

void colossusInit(ColossusConfig config, ECS **ecs)
{
    graphicsInit(config.graphics_config);
    resourceManagerInit();

    *ecs = ecsCreate(config.max_entities, SYS_COUNT);
    ecsAddonCore(*ecs, SYS_UPDATE);
    ecsAddonGraphics(*ecs, SYS_UPDATE);
}

void colossusSetup(ECS *ecs)
{
    ecsBake(ecs);
}

void colossusStart(ECS *ecs)
{
    while (graphicsRunning()) {
        graphicsLoopBegin();
        beginBatch();

        ecsRun(ecs, SYS_PRE_UPDATE);
        ecsRun(ecs, SYS_UPDATE);
        ecsRun(ecs, SYS_LATE_UPDATE);
        
        endBatch();
        flushBatch();
        graphicsLoopEnd();
    }
}

void colossusTerminate(ECS **ecs)
{
    graphicsTerminate();
    resourceManagerTerminate();

    ecsDestroy(ecs);
}
