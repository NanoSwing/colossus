#include "engine/internal_engine.h"
#include "colossus/ecs_addons/core_ecs.h"
#include "colossus/ecs_addons/graphics_ecs.h"

#include <stdlib.h>

GlobalState global = {0};

Engine *engineCreate(I32 width, I32 height, const char *title, B8 resizable, I32 max_entity_count, ECS **ecs)
{
    Engine *engine = malloc(sizeof(Engine));

    engine->ecs = ecsCreate(max_entity_count, SYS_GROUP_COUNT);
    engine->graphics = graphicsInit(width, height, title, resizable);
    engine->pipeline = pipelineCreate(engine->graphics);

    *ecs = engine->ecs;

    return engine;
}

void engineSetup(Engine *engine)
{
    ecsAddonCore(engine->ecs, SYS_UPDATE);
    ecsAddonGraphics(engine->ecs, SYS_UPDATE);

    ecsBake(engine->ecs);
}

static void loop(void *args)
{
    Engine *engine = args;

    ecsRun(engine->ecs, SYS_PRE_UPDATE);
    ecsRun(engine->ecs, SYS_UPDATE);
    ecsRun(engine->ecs, SYS_LATE_UPDATE);

    pipelineRender(engine->pipeline, engine->ecs);
}
void engineStart(Engine *engine) { graphicsLoop(engine->graphics, loop, engine); }

void engineDestroy(Engine **engine)
{
    ecsDestroy(&(*engine)->ecs);
    pipelineDestroy((*engine)->pipeline);
    graphicsTerminate((*engine)->graphics);
    free(*engine);
    *engine = NULL;
}
