#include "ecs/internal_ecs.h"
#include "colossus/ecs/entity.h"
#include "colossus/core/da.h"

#include <malloc.h>
#include <string.h>

ECS *ecsCreate(U32 max_entity_count, U32 system_group_count)
{
    ECS *ecs = malloc(sizeof(ECS));

    ecs->max_entity_count = max_entity_count;
    ecs->current_entity_id = 0;

    ecs->components = daCreate(sizeof(Component));

    ecs->systems = daCreate(sizeof(System *));
    for (U32 i = 0; i < system_group_count; i++) {
        daPush(ecs->systems, daCreate(sizeof(System)));
    }

    return ecs;
}

void ecsDestroy(ECS **ecs)
{
    for (U32 i = 0; i < daCount((*ecs)->components); i++) {
        daDestroy((*ecs)->components[i].entities);
        free((*ecs)->components[i].storage);
    }
    daDestroy((*ecs)->components);
    
    free((*ecs)->entity_component_table);

    for (U32 i = 0; i < daCount((*ecs)->systems); i++) {
        daDestroy((*ecs)->systems[i]);
    }
    daDestroy((*ecs)->systems);

    free(*ecs);
    *ecs = NULL;
}

void ecsBake(ECS *ecs)
{
    ecs->entity_component_table = calloc(daCount(ecs->components), ecs->max_entity_count);
}

void ecsAddComponent(ECS *ecs, U64 size)
{
    Component *comp = daPush(ecs->components, NULL);
    memcpy((U64 *) &comp->size, &size, sizeof(U64));
    comp->entities = daCreate(sizeof(Entity));
    comp->storage = malloc(size * ecs->max_entity_count);
}

const Component *ecsGetComponent(ECS *ecs, U32 component_id)
{
    return &ecs->components[component_id];
}

void ecsAddSystem(ECS *ecs, U32 system_group_id, System system)
{
    daPush(ecs->systems[system_group_id], system);
}

I32 ecsRun(ECS *ecs, U32 system_group_id)
{
    if (system_group_id >= daCount(ecs->systems)) {
        return false;
    }

    for (U32 i = 0; i < daCount(ecs->systems[system_group_id]); i++) {
        ecs->systems[system_group_id][i](ecs);
    }

    return true;
}

U32 internalEcsGetEntityID(ECS *ecs)
{
    return ecs->current_entity_id++;
}

void ecsDebugPrintTable(ECS *ecs)
{
    for (U32 y = 0; y < daCount(ecs->components); y++) {
        for (U32 x = 0; x < ecs->max_entity_count; x++) {
            printf("%d ", ecs->entity_component_table[x + y * ecs->max_entity_count]);
        }
        printf("\n");
    }
}
