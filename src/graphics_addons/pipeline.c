#include "graphics_addons/internal_pipeline.h"
#include "graphics/internal_graphics.h"
#include "ecs/internal_ecs.h"
#include "colossus/ecs_addons/graphics_ecs.h"
#include "colossus/ecs_addons/core_ecs.h"
#include "colossus/core/da.h"
#include "colossus/core/logger.h"

#include <stdlib.h>

#include <glad/glad.h>

#define MAX_QUAD_COUNT 1024
#define MAX_VERTEX_COUNT MAX_QUAD_COUNT * 4
#define MAX_INDEX_COUNT MAX_QUAD_COUNT * 6

Pipeline *pipelineCreate(Graphics *graphics)
{
    Pipeline *pl = malloc(sizeof(Pipeline));

    // Vertex layout for quad batcher
    VertexLayout layout[] = {
        { .offset = offsetof(Vertex, pos),    .size = 2 },  
        { .offset = offsetof(Vertex, uv),     .size = 2 },  
        { .offset = offsetof(Vertex, tex_id), .size = 1 },  
        { .offset = offsetof(Vertex, color),  .size = 4 }  
    };

    // Quad batcehr indices
    I32 indices[MAX_INDEX_COUNT] = {0};
    I32 offset = 0;
    for (I32 i = 0; i < MAX_INDEX_COUNT; i += 6) {
        indices[i + 0] = offset + 0;
        indices[i + 1] = offset + 1;
        indices[i + 2] = offset + 2;

        indices[i + 3] = offset + 2;
        indices[i + 4] = offset + 3;
        indices[i + 5] = offset + 1;
        
        offset += 4;
    }

    // Quad batcher
    pl->batcher = batcherCreate(sizeof(Vertex), MAX_VERTEX_COUNT, layout, sizeof(layout) / sizeof(layout[0]), indices, MAX_INDEX_COUNT);
    
    // Configure texture indices
    I32 samplers[32] = {0};
    for (I32 i = 0; i < 32; i++) { samplers[i] = i; }
    pl->shader = shaderCreate("colossus/assets/shaders/default.vert", "colossus/assets/shaders/default.frag");
    shaderUse(pl->shader);
    shaderUniformIv(pl->shader, "textures", 32, samplers);

    // Create blank texture for rendering quads without texture.
    I32 white = 0xFFFFFFFF;
    pl->textures[0] = textureFromPixels(1, 1, SCALE_NEAREST, 4, &white);
    pl->texture_count = 1;

    pl->graphics = graphics;
    pl->lines = daCreate(sizeof(LineCall));

    // Barebones quad vertex
    typedef struct {
        Vec2 pos;
        Vec2 uv;
    } QuadVert;

    // Create a framebuffer for rendering to
    Texture screen_texture = textureFromPixels(graphics->width, graphics->height, SCALE_NEAREST, 4, NULL);
    pl->screen_fbo = fboCreate(screen_texture);
    
    // Quad convering entire screen
    QuadVert quad_vertices[4] = {
        {vec2(-1.0f, -1.0f), vec2(0.0f, 0.0f)},
        {vec2( 1.0f, -1.0f), vec2(1.0f, 0.0f)},
        {vec2(-1.0f,  1.0f), vec2(0.0f, 1.0f)},
        {vec2( 1.0f,  1.0f), vec2(1.0f, 1.0f)}
    };
    // Quad indices
    I32 quad_indices[6] = {
        0, 1, 2,
        2, 3, 1
    };

    // Create rendering buffers for quad
    pl->quad_vao = vaoCreate();
    pl->quad_vbo = vboCreateStatic(sizeof(QuadVert), 4, quad_vertices);
    pl->quad_ebo = eboCreate(quad_indices, 6);

    pl->quad_shader = shaderCreate("colossus/assets/shaders/quad.vert", "colossus/assets/shaders/quad.frag");

    // Vertex layout for barebones quad
    VertexLayout quad_layout[2] = {
        {.offset = offsetof(QuadVert, pos), .size = 2},
        {.offset = offsetof(QuadVert, uv), .size = 2}
    };
    vaoAddVBO(pl->quad_vao, pl->quad_vbo, sizeof(QuadVert), quad_layout, 2);

    return pl;
}

void pipelineDestroy(Pipeline *pipeline)
{
    batcherDestroy(&pipeline->batcher);
    shaderDestroy(pipeline->shader);
    textureDestroy(pipeline->textures[0]);

    vaoDestroy(pipeline->quad_vao);
    vboDestroy(pipeline->quad_vbo);
    eboDestroy(pipeline->quad_ebo);
    shaderDestroy(pipeline->quad_shader);
}

typedef struct {
    Entity ent;
    SpriteRenderer sr;
} EntitySpriteSortContainer;
static I32 compareEntityZIndex(const void *_a, const void *_b)
{
    const EntitySpriteSortContainer *a = _a;
    const EntitySpriteSortContainer *b = _b;
    return compInt(&a->sr.z_index, &b->sr.z_index);
}
void pipelineRender(Pipeline *pipeline, ECS *ecs)
{   
    I32 width = pipeline->graphics->width;
    I32 height = pipeline->graphics->height;

    // Create projection
    Mat4 proj = mat4OrthoProjection(-(F32) width * 0.5f, (F32) width * 0.5f, (F32) height * 0.5f, -(F32) height * 0.5f, -1, 1);

    // Resize framebuffer texture
    textureResize(&pipeline->screen_fbo.color_attachment, width, height, NULL);

    // Render to framebuffer
    fboBind(pipeline->screen_fbo);
    glClearColor(hexRGBA_1(0x191919ff));
    glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  

    // Bind shader
    shaderUse(pipeline->shader);
    shaderUniformMat4(pipeline->shader, "projection", proj);

    // Upload textures
    for (I32 i = 0; i < pipeline->texture_count; i++) {
        textureBindUnit(i, pipeline->textures[i]);
    }

    // Render entities
    const Component *comp = ecsGetComponent(ecs, COMP_SPRITE_RENDERER);
    SpriteRenderer *sr = comp->storage;

    // Sort entities based on z-index
    EntitySpriteSortContainer *sorted_ents = daCreate(sizeof(EntitySpriteSortContainer));
    for (I32 i = 0; i < daCount(comp->entities); i++) {
        daPush(sorted_ents, ((EntitySpriteSortContainer) {.ent = comp->entities[i], .sr = sr[comp->entities[i].id]}));
    }
    qsort(sorted_ents, daCount(sorted_ents), sizeof(EntitySpriteSortContainer), compareEntityZIndex);

    Transform *trans = ecsGetComponent(ecs, COMP_TRANSFORM)->storage;
    for (I32 i = 0; i < daCount(sorted_ents); i++) {
        Entity ent = sorted_ents[i].ent;
        if (!entityHasComponent(ent, COMP_TRANSFORM)) {
            continue;
        }
        I32 e = ent.id;

        // Standard variables for rendering without an animation component
        I32 frame_count = 1;
        I32 frame = 0;

        // Configure for animation
        Animation *anim = entityGetComponent(ent, COMP_ANIMATION);
        if (anim != NULL) {   
            frame_count = anim->frame_count;
            frame = anim->frame;
        }

        // Batch the entity
        drawQuad(pipeline, trans[e].position, trans[e].scale, trans[e].rotation, sr[e].color, sr[e].texture, frame_count, frame);
    }
    daDestroy(sorted_ents);

    // Render the batch
    batcherFlush(&pipeline->batcher);

    // Stop rendering to framebuffer
    fboUnbind();

    // Render to screen
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Render framebuffer texture to screen
    textureBind(pipeline->screen_fbo.color_attachment);
    shaderUse(pipeline->quad_shader);
    vaoBind(pipeline->quad_vao);
    eboBind(pipeline->quad_ebo);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
    vaoUnbind();
    eboUnbind();

    // Render lines to buffer
    fboBind(pipeline->screen_fbo);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);


    shaderUse(pipeline->shader);
    shaderUniformMat4(pipeline->shader, "projection", proj);

    // Upload textures
    for (I32 i = 0; i < pipeline->texture_count; i++) {
        textureBindUnit(i, pipeline->textures[i]);
    }
    // Reset textures
    pipeline->texture_count = 1;

    LineCall call;
    for (I32 i = 0; i < daCount(pipeline->lines); i++) {
        daPop(pipeline->lines, &call);

        Vec2 line_pos = vec2MulS(vec2Sub(call.b, call.a), 0.5f);
        F32 len = vec2Mag(vec2Sub(call.b, call.a));
        F32 opposite = call.b.y - call.a.y;
        F32 adjacent = call.b.x - call.a.x;
        F32 angle = atan(opposite / adjacent);

        drawQuad(pipeline, line_pos, vec2(call.thickness, len), 90 - deg(angle), call.color, NULL_TEXTURE, 1, 0);
    }
    batcherFlush(&pipeline->batcher);

    fboUnbind();

    // Render framebuffer texture to screen
    textureBind(pipeline->screen_fbo.color_attachment);
    shaderUse(pipeline->quad_shader);
    vaoBind(pipeline->quad_vao);
    eboBind(pipeline->quad_ebo);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
    vaoUnbind();
    eboUnbind();
}

void drawQuad(Pipeline *pipeline, Vec2 position, Vec2 size, F32 rotation, Vec4 color, Texture texture, I32 frame_count, I32 frame)
{
    Batcher *batcher = &pipeline->batcher;

    // If any caps are reached, flush
    if (batcher->vertex_count == batcher->max_vertex_count || pipeline->texture_count == 32) {
        batcherFlush(batcher);
    }

    // Handle textures
    B8 found = false;
    I32 texture_index = 0;
    if (textureIsNULL(texture)) {
        found = true;
    } else {
        for (I32 i = 0; i < pipeline->texture_count; i++) {
            if (pipeline->textures[i].id == texture.id) {
                found = true;
                texture_index = i;
                break;
            }
        }

        if (!found) {
            pipeline->textures[pipeline->texture_count] = texture;
            texture_index = pipeline->texture_count;
            pipeline->texture_count++;
        }
    }

    Vertex *buffer = batcher->vertex_buffer;
    I32 *index = &batcher->vertex_count;

    // Vertex positions
    const Vec2 pos[4] = {
        vec2(-0.5f, -0.5f), // Bottom left
        vec2( 0.5f, -0.5f), // Bottom right
        vec2(-0.5f,  0.5f), // Top left
        vec2( 0.5f,  0.5f)  // Top right
    };

    // Height in pixels per frame in spirte sheet
    I32 frame_height = texture.height / frame_count;
    // Calculate UV coordinates for texture
    const Vec2 uvs[4] = {
        vec2(0.0f, (F32) ((frame_count - frame - 1) * frame_height) / (F32) texture.height),
        vec2(1.0f, (F32) ((frame_count - frame - 1) * frame_height) / (F32) texture.height),
        vec2(0.0f, (F32) ((frame_count - frame) * frame_height) / (F32) texture.height),
        vec2(1.0f, (F32) ((frame_count - frame) * frame_height) / (F32) texture.height)
    };
    
    // Update vertices
    for (I32 i = 0; i < 4; i++) {
        Vec2 vert_pos = pos[i];
        // Transform vertex to correct position
        vert_pos = vec2Mul(vert_pos, size);
        vert_pos = vec2Rot(vert_pos, rotation);
        vert_pos = vec2Add(vert_pos, position);
        // Transform for camera
        vert_pos = vec2Sub(vert_pos, pipeline->graphics->cam.position);

        // vert_pos = vec2MulS(vert_pos, 1.0f / pipeline->graphics->cam.scale);
        vert_pos = vec2Floor(vert_pos);
        vert_pos = vec2AddS(vert_pos, 0.5f);
        
        buffer[*index].pos = vert_pos;

        // Assign UV
        buffer[*index].uv = uvs[i];
        // Assign color
        buffer[*index].color = color;
        // Assign texture id
        buffer[*index].tex_id = (F32) texture_index;

        // Increase vertex count/index
        (*index)++;
    }
}

void drawLineLength(Pipeline *pipeline, Vec2 start, F32 length, F32 angle, F32 thickness, Vec4 color)
{
    Vec2 b = vec2(0, 1);
    b = vec2Rot(b, angle);
    b = vec2MulS(b, length);
    LineCall call = {
        .a = start,
        .b = b,
        .thickness = thickness,
        .color = color
    };
    daPush(pipeline->lines, call);
}

void drawLinePoints(Pipeline *pipeline, Vec2 a, Vec2 b, F32 thickness, Vec4 color)
{
    LineCall call = {
        .a = a,
        .b = b,
        .thickness = thickness,
        .color = color
    };
    daPush(pipeline->lines, call);
}
