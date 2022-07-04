#pragma once

#include "colossus/ecs/ecs.h"
#include "colossus/core/queue.h"

struct ECS {
    I32 max_entity_count;

    I32 *available_entities; // Dynamic array
    Component *components; // Dynamic array
    System **systems; // Dynamic array

    B8 *entity_component_table;
};

extern I32 internalEcsGetEntityID(ECS *ecs);
