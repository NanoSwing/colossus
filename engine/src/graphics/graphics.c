#include "graphics/internal_graphics.h"
#include "graphics/callbacks.h"
#include "colossus/core/logger.h"
#include "colossus/core/da.h"

#include <malloc.h>
#include <math.h>

#include <glad/glad.h>

/* Define global graphics context. */
GraphicsContext g_context = { 0 };

void initGraphics(GraphicsConfig config)
{
    g_context.config = config;

    if (!glfwInit()) {
        logFatal("GLFW failed to initialize!");
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, config.resizable);

    g_context.window = glfwCreateWindow(config.width, config.height, config.title, NULL, NULL);
    if (g_context.window == NULL) {
        terminateGraphics();
        logFatal("Window creation failed!");
    }
    glfwMakeContextCurrent(g_context.window);
    glfwSetFramebufferSizeCallback(g_context.window, framebufferSizeCallback);
    // Turn off fps limit / vsync
    glfwSwapInterval(0);
    
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        terminateGraphics();
        logFatal("Glad failed to initialize!");
    }

    // Create quad batcher
    Layout *quad_layout = daCreate(sizeof(Layout));
    daPush(quad_layout, ((Layout) {.size = 2, offsetof(Vertex, position)}));
    daPush(quad_layout, ((Layout) {.size = 4, offsetof(Vertex, color)}));
    daPush(quad_layout, ((Layout) {.size = 1, offsetof(Vertex, texture_id)}));
    daPush(quad_layout, ((Layout) {.size = 2, offsetof(Vertex, texture_coords)}));
    Shader shader = shaderCreate("assets/shaders/quad.vert", "assets/shaders/quad.frag");
    g_context.quad_batcher = createBatcher(1024, sizeof(Vertex), quad_layout, &g_context.projection, shader);
    daDestroy(quad_layout);

    // Create line batcher
    Layout *line_layout = daCreate(sizeof(Layout));
    daPush(line_layout, ((Layout) {.size = 2, offsetof(LineVertex, position)}));
    daPush(line_layout, ((Layout) {.size = 4, offsetof(LineVertex, color)}));
    Shader line_shader = shaderCreate("assets/shaders/line.vert", "assets/shaders/line.frag");
    g_context.line_batcher = createBatcher(1024, sizeof(LineVertex), line_layout, &g_context.projection, line_shader);
    daDestroy(line_layout);

    // Enable blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    logInfo("Graphics initialized successfully!");
}

void terminateGraphics(void)
{
    destroyBatcher(g_context.quad_batcher);
    destroyBatcher(g_context.line_batcher);

    if (g_context.window != NULL) {
        glfwDestroyWindow(g_context.window);
    }
    glfwTerminate();
}


B8 graphicsRunning(void)
{
    return !glfwWindowShouldClose(g_context.window);
}

void graphicsLoopBegin(void)
{
    glClearColor(g_context.config.red, g_context.config.green, g_context.config.blue, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Update projection
    I32 width, height;
    glfwGetWindowSize(g_context.window, &width, &height);
    F32 scale = g_context.config.scale / 2.0f;
    F32 scale_factor = ((F32) width / (F32) height) * scale;
    g_context.projection = mat4OrthoProjection(-scale_factor, scale_factor, scale, -scale, -1, 1);
}
void graphicsLoopEnd(void)
{
    glfwSwapBuffers(g_context.window);
    glfwPollEvents();
}

void beginBatch(void)
{
    startBatcher(&g_context.quad_batcher);
    startBatcher(&g_context.line_batcher);
}
void flushBatch(void)
{
    flushBatcher(&g_context.quad_batcher);
    flushBatcher(&g_context.line_batcher);
}
void endBatch(void)
{
    endBatcher(&g_context.quad_batcher);
    endBatcher(&g_context.line_batcher);
}

void drawQuad(Vec2 pos, Vec2 size, F32 rotation, Vec4 color, Texture texture, I32 frame_count, I32 frame)
{
    Batcher *quad_batcher = &g_context.quad_batcher;
    U32 texture_index;
    batchQuad(quad_batcher, texture.id, &texture_index);

    Vertex *buffer_pointer = quad_batcher->quad_pointer;

    F32 sprite_height = (F32) texture.height / (F32) frame_count;
    F32 sheet_height = (F32) texture.height;

    // Bottom left
    Vec2 bl = vec2(-0.5f, -0.5f);
    bl = vec2Mul(bl, size);
    bl = vec2Rot(bl, rotation);
    bl = vec2Add(bl, pos);
    buffer_pointer->position = bl;
    buffer_pointer->color = color;
    buffer_pointer->texture_id = (F32) texture_index;
    buffer_pointer->texture_coords = vec2(0.0f, ((F32) (frame_count - frame - 1) * sprite_height) / sheet_height);
    buffer_pointer++;

    // Bottom right
    Vec2 br = vec2( 0.5f, -0.5f);
    br = vec2Mul(br, size);
    br = vec2Rot(br, rotation);
    br = vec2Add(br, pos);
    buffer_pointer->position = br;
    buffer_pointer->color = color;
    buffer_pointer->texture_id = (F32) texture_index;
    buffer_pointer->texture_coords = vec2(1.0f, ((F32) (frame_count - frame - 1) * sprite_height) / sheet_height);
    buffer_pointer++;
    
    // Top left
    Vec2 tl = vec2(-0.5f,  0.5f);
    tl = vec2Mul(tl, size);
    tl = vec2Rot(tl, rotation);
    tl = vec2Add(tl, pos);
    buffer_pointer->position = tl;
    buffer_pointer->color = color;
    buffer_pointer->texture_id = (F32) texture_index;
    buffer_pointer->texture_coords = vec2(0.0f, (((F32) (frame_count - frame - 1) + 1.0f) * sprite_height) / sheet_height);
    buffer_pointer++;
    
    // Top right
    Vec2 tr = vec2( 0.5f,  0.5f);
    tr = vec2Mul(tr, size);
    tr = vec2Rot(tr, rotation);
    tr = vec2Add(tr, pos);
    buffer_pointer->position = tr;
    buffer_pointer->color = color;
    buffer_pointer->texture_id = (F32) texture_index;
    buffer_pointer->texture_coords = vec2(1.0f, (((F32) (frame_count - frame - 1) + 1.0f) * sprite_height) / sheet_height);
    buffer_pointer++;

    quad_batcher->quad_pointer = buffer_pointer;
}

static void drawLine(Vec2 start, Vec2 end, F32 thickness, Vec4 color)
{
    Batcher *batcher = &g_context.line_batcher;
    batchQuad(batcher, 0, NULL);

    LineVertex *buffer_pointer = batcher->quad_pointer;

    Vec2 magic_vector = vec2Sub(end, start);
    F32 length = vec2Mag(magic_vector);

    F32 angle = 90.0f - deg(atan(magic_vector.y / magic_vector.x));
    Vec2 size = vec2(thickness, length);
    Vec2 pos = vec2Add(start, vec2DivS(magic_vector, 2));

    const Vec2 positions[4] = {
        vec2(-0.5f, -0.5f),
        vec2( 0.5f, -0.5f),
        vec2(-0.5f,  0.5f),
        vec2( 0.5f,  0.5f)
    };

    for (U32 i = 0; i < 4; i++) {
        Vec2 vert_pos = positions[i];
        vert_pos = vec2Mul(vert_pos, size);
        vert_pos = vec2Rot(vert_pos, angle);
        vert_pos = vec2Add(vert_pos, pos);
        buffer_pointer->position = vert_pos;
        buffer_pointer->color = color;
        buffer_pointer++;
    }

    batcher->quad_pointer = buffer_pointer;
}

void drawColor(Vec2 pos, Vec2 size, F32 rotation, Vec4 color)
{
    drawQuad(pos, size, rotation, color, ((Texture) {.id = 0}), 1, 0);
}

void drawTexture(Vec2 pos, Vec2 size, F32 rotation, Texture texture)
{
    drawQuad(pos, size, rotation, vec4s(1), texture, 1, 0);
}

void drawSpriteSheet(Vec2 pos, Vec2 size, F32 rotation, SpriteSheet sheet, I32 frame)
{
    drawQuad(pos, size, rotation, vec4s(1), sheet.texture, sheet.frame_count, frame);
}

void drawLinePoints(Vec2 start, Vec2 end, F32 thickness, Vec4 color)
{
    drawLine(start, end, thickness, color);
}

void drawLineLength(Vec2 start, F32 length, F32 angle, F32 thickness, Vec4 color)
{
    Vec2 end = vec2(0, length);
    end = vec2Rot(end, angle);

    drawLine(start, end, thickness, color);
}
