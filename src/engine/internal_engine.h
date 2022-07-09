#pragma once

#include "colossus/engine/engine.h"
#include "colossus/ecs/ecs.h"
#include "colossus/graphics/graphics.h"
#include "colossus/graphics_addons/pipeline.h"

struct Engine {
    ECS *ecs;
    Graphics *graphics;
    Pipeline *pipeline;
};
