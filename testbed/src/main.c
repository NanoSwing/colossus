#include <stdio.h>
#include <string.h>

#include "colossus/colossus.h"

#include "colossus/ecs/ecs.h"
#include "colossus/ecs/entity.h"

typedef struct {
    F32 x, y;
} Vec2F32;

typedef enum {
    COMP_POSITION,
    COMP_VELOCITY
} ComponentID;

typedef enum {
    SYS_UPDATE,
} SystemGroup;

void testSys(ECS *ecs)
{
    const Component *position_comp = ecsGetComponent(ecs, COMP_POSITION);
    Vec2F32 *pos = position_comp->storage;
    Vec2F32 *vel = ecsGetComponent(ecs, COMP_VELOCITY)->storage;

    for (U32 i = 0; i < daCount(position_comp->entities); i++) {
        Entity ent = position_comp->entities[i];
        if (!entityHasComponent(ent, COMP_VELOCITY)) {
            continue;
        }

        pos[ent.ID].x += vel[ent.ID].x;
        pos[ent.ID].y += vel[ent.ID].y;
        printf("%d: %f, %f\n", ent.ID, pos[ent.ID].x, pos[ent.ID].y);
    }
}

I32 main(void)
{
    ECS *ecs = ecsCreate(16, 1);

    ecsAddComponent(ecs, sizeof(Vec2F32)); // Position
    ecsAddComponent(ecs, sizeof(Vec2F32)); // Velocity

    ecsAddSystem(ecs, SYS_UPDATE, testSys);

    ecsBake(ecs);

    Entity ent = ecsCreateEntity(ecs);
    entityAddComponent(ent, COMP_POSITION);
    entityAddComponent(ent, COMP_VELOCITY);
    Vec2F32 *vel = entityGetComponent(ent, COMP_VELOCITY);
    vel->x = 3.14f;
    vel->y = vel->x * 2.0f;

    ecsRun(ecs, SYS_UPDATE);

    ecsDestroy(&ecs);
    return 0;
}
