#include <stdio.h>

#include "colossus/colossus.h"

typedef struct {
    F32 x, y;
} Vec2F32;

U32 COMP_POSITION = -1;
U32 COMP_VELCOITY = -1;

void accelerate(ECS *ecs)
{
    // Get the position component.
    const Component *comp = ecsGetComponent(ecs, COMP_VELCOITY);
    
    // Convert component data into a Vec2F32 array.
    Vec2F32 *velocity = comp->storage;
    // Get the component data for position.
    Vec2F32 *position = ecsGetComponent(ecs, COMP_POSITION)->storage;
    
    // Iterate over all entities with velocity components attached.
    for (U32 i = 0; i < daCount(comp->entities); i++) {
        Entity ent = comp->entities[i];
        // Check if entity has a position.
        if (!entityHasComponent(ent, COMP_POSITION)) {
            continue;
        }

        // Update position with velocity.
        position[ent.ID].x += velocity[ent.ID].x;
        position[ent.ID].y += velocity[ent.ID].y;

        // Print new positions.
        printf("%u: %f, %f\n", ent.ID, position[ent.ID].x, position[ent.ID].y);
    }
}

I32 main(void)
{
    // Create an ECS with space for 16 entities and 1 system group.
    ECS *ecs = ecsCreate(16, 1);

    // Add components and assign their values to variables.
    COMP_POSITION = ecsAddComponent(ecs, sizeof(Vec2F32));
    COMP_VELCOITY = ecsAddComponent(ecs, sizeof(Vec2F32));

    // Add accelerate to system group 0
    ecsAddSystem(ecs, accelerate, 0);

    // Tell ECS we're done adding components.
    // Finalizes configuration-
    ecsBake(ecs);

    // Create an entity
    Entity player = ecsCreateEntity(ecs);
    // Add components
    entityAddComponent(player, COMP_POSITION);
    entityAddComponent(player, COMP_VELCOITY);
    // Configure velocity component
    Vec2F32 *vel = entityGetComponent(player, COMP_VELCOITY);
    *vel = (Vec2F32) { 1.0f, 1.0f };

    // Run system group 0 ten times.
    for (U32 i = 0; i < 10; i++) {
        ecsRun(ecs, 0);
    }

    // Destroy the ECS.
    ecsDestroy(&ecs);
    return 0;
}
