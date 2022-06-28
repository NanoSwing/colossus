#pragma once

#include "colossus/ecs/ecs.h"

struct ECS {
    U32 max_entity_count;
    U32 current_entity_id;

    Component *components; // Dynamic array
    System **systems; // Dynamic array

    B8 *entity_component_table;
};

extern U32 internalEcsGetEntityID(ECS *ecs);
