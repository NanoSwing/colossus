#include "graphics_addons/internal_pipeline.h"
#include "graphics/internal_graphics.h"
#include "colossus/ecs_addons/graphics_ecs.h"
#include "colossus/ecs_addons/core_ecs.h"
#include "colossus/core/da.h"
#include "colossus/core/logger.h"

#include <stdlib.h>

#include <glad/glad.h>

#define MAX_QUAD_COUNT 1024
#define MAX_VERTEX_COUNT MAX_QUAD_COUNT * 4
#define MAX_INDEX_COUNT MAX_QUAD_COUNT * 6

Pipeline *pipelineCreate(Graphics *graphics, I32 pixels_per_unit)
{
    Pipeline *pl = malloc(sizeof(Pipeline));

    VertexLayout layout[] = {
        { .offset = offsetof(Vertex, pos),    .size = 2 },  
        { .offset = offsetof(Vertex, uv),     .size = 2 },  
        { .offset = offsetof(Vertex, tex_id), .size = 1 },  
        { .offset = offsetof(Vertex, color),  .size = 4 }  
    };

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

    pl->batcher = batcherCreate(sizeof(Vertex), MAX_VERTEX_COUNT, layout, sizeof(layout) / sizeof(layout[0]), indices, MAX_INDEX_COUNT);
    
    I32 samplers[32] = {0};
    for (I32 i = 0; i < 32; i++) { samplers[i] = i; }
    pl->shader = shaderCreate("colossus/assets/shaders/default.vert", "colossus/assets/shaders/default.frag");
    shaderUse(pl->shader);
    shaderUniformIv(pl->shader, "textures", 32, samplers);

    I32 white = 0xFFFFFFFF;
    pl->textures[0] = textureFromPixels(1, 1, SCALE_NEAREST, 4, &white);
    pl->texture_count = 1;

    pl->graphics = graphics;
    pl->pixels_per_unit = pixels_per_unit;

    {
        typedef struct {
            Vec2 pos;
            Vec2 uv;
        } QuadVert;

        Texture screen_texture = textureFromPixels(graphics->width, graphics->height, SCALE_NEAREST, 4, NULL);
        pl->screen_fbo = fboCreate(screen_texture);
        
        QuadVert quad_vertices[4] = {
            {vec2(-1.0f, -1.0f), vec2(0.0f, 0.0f)},
            {vec2( 1.0f, -1.0f), vec2(1.0f, 0.0f)},
            {vec2(-1.0f,  1.0f), vec2(0.0f, 1.0f)},
            {vec2( 1.0f,  1.0f), vec2(1.0f, 1.0f)}
        };
        I32 quad_indices[6] = {
            0, 1, 2,
            2, 3, 1
        };
        pl->quad_vao = vaoCreate();
        pl->quad_vbo = vboCreateStatic(sizeof(QuadVert), 4, quad_vertices);
        pl->quad_ebo = eboCreate(quad_indices, 6);

        pl->quad_shader = shaderCreate("colossus/assets/shaders/quad.vert", "colossus/assets/shaders/quad.frag");

        VertexLayout quad_layout[2] = {
            {.offset = offsetof(QuadVert, pos), .size = 2},
            {.offset = offsetof(QuadVert, uv), .size = 2}
        };
        vaoAddVBO(pl->quad_vao, pl->quad_vbo, sizeof(QuadVert), quad_layout, 2);
    }

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

void pipelineRender(Pipeline *pipeline, ECS *ecs)
{   
    I32 width = pipeline->graphics->width;
    I32 height = pipeline->graphics->height;

    // Mat4 proj = mat4OrthoProjection(-(F32) width / 2.0f, (F32) width / 2.0f, (F32) height / 2.0f, -(F32) height / 2.0f, -1, 1);
    Mat4 proj = {
        {width / 2.0f, 0.0f,          0.0f, 0.0f},
        {0.0f,         height / 2.0f, 0.0f, 0.0f},
        {0.0f,         0.0f,          1.0f, 0.0f},
        {0.0f,         0.0f,          0.0f, 1.0f}
    };
    proj = mat4Inverse(proj);

    textureResize(&pipeline->screen_fbo.color_attachment, width, height, NULL);

    fboBind(pipeline->screen_fbo);
    glClearColor(hexRGBA_1(0x191919ff));
    glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  

    shaderUse(pipeline->shader);
    shaderUniformMat4(pipeline->shader, "projection", proj);

    for (I32 i = 0; i < pipeline->texture_count; i++) {
        textureBindUnit(i, pipeline->textures[i]);
    }
    pipeline->texture_count = 1;

    const Component *comp = ecsGetComponent(ecs, COMP_SPRITE_RENDERER);
    SpriteRenderer *sr = comp->storage;
    Transform *trans = ecsGetComponent(ecs, COMP_TRANSFORM)->storage;
    for (I32 i = 0; i < daCount(comp->entities); i++) {
        Entity ent = comp->entities[i];
        if (!entityHasComponent(ent, COMP_TRANSFORM)) {
            continue;
        }
        I32 e = ent.id;

        I32 frame_count = 1;
        I32 frame = 0;

        if (entityHasComponent(ent, COMP_ANIMATION)) {
            Animation *anim = entityGetComponent(ent, COMP_ANIMATION);
            frame_count = anim->frame_count;
            frame = anim->frame;
        }

        drawQuad(pipeline, trans[e].position, trans[e].scale, trans[e].rotation, sr[e].color, sr[e].texture, frame_count, frame);
    }

    batcherFlush(&pipeline->batcher);

    // Screen buffer
    fboUnbind();

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    textureBind(pipeline->screen_fbo.color_attachment);
    shaderUse(pipeline->quad_shader);
    shaderUniformMat4(pipeline->quad_shader, "projection", proj);
    vaoBind(pipeline->quad_vao);
    eboBind(pipeline->quad_ebo);
    
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);

    vaoUnbind();
    eboUnbind();
}

void drawQuad(Pipeline *pipeline, Vec2 position, Vec2 size, F32 rotation, Vec4 color, Texture texture, I32 frame_count, I32 frame)
{
    Batcher *batcher = &pipeline->batcher;

    if (batcher->vertex_count == batcher->max_vertex_count || pipeline->texture_count == 32) {
        batcherFlush(batcher);
    }

    // Handle textures
    B8 found = false;
    I32 texture_index = 0;
    if (texture.id == NULL_TEXTURE.id) {
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

    const Vec2 pos[4] = {
        vec2(-0.5f, -0.5f),
        vec2( 0.5f, -0.5f),
        vec2(-0.5f,  0.5f),
        vec2( 0.5f,  0.5f)
    };

    I32 frame_height = texture.height / frame_count;
    const Vec2 uvs[4] = {
        vec2(0.0f, (F32) ((frame_count - frame - 1) * frame_height) / (F32) texture.height),
        vec2(1.0f, (F32) ((frame_count - frame - 1) * frame_height) / (F32) texture.height),
        vec2(0.0f, (F32) ((frame_count - frame) * frame_height) / (F32) texture.height),
        vec2(1.0f, (F32) ((frame_count - frame) * frame_height) / (F32) texture.height)
    };
    
    for (I32 i = 0; i < 4; i++) {

        Vec2 vert_pos = pos[i];
        vert_pos = vec2Mul(vert_pos, vec2MulS(size, pipeline->pixels_per_unit));
        vert_pos = vec2Rot(vert_pos, rotation);
        vert_pos = vec2Add(vert_pos, vec2MulS(position, pipeline->pixels_per_unit));
        buffer[*index].pos = vert_pos;

        buffer[*index].uv = uvs[i];
        buffer[*index].color = color;
        buffer[*index].tex_id = (F32) texture_index;

        (*index)++;
    }
}
