#include "graphics/internal_graphics.h"
#include "graphics/callbacks.h"
#include "colossus/core/logger.h"
#include "colossus/core/da.h"

#include <malloc.h>

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
    // Turn off fps limit
    glfwSwapInterval(0);

    g_context.window = glfwCreateWindow(config.width, config.height, config.title, NULL, NULL);
    if (g_context.window == NULL) {
        terminateGraphics();
        logFatal("Window creation failed!");
    }
    glfwMakeContextCurrent(g_context.window);
    glfwSetFramebufferSizeCallback(g_context.window, framebufferSizeCallback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        terminateGraphics();
        logFatal("Glad failed to initialize!");
    }

    // Create batcher
    Layout *layout = daCreate(sizeof(Layout));
    daPush(layout, ((Layout) {.size = 2, offsetof(Vertex, position)}));
    daPush(layout, ((Layout) {.size = 3, offsetof(Vertex, color)}));
    Shader shader = shaderCreate("assets/shaders/default.vert", "assets/shaders/default.frag");
    g_context.batcher = createBatcher(1024, sizeof(Vertex), layout, &g_context.projection, shader);
    daDestroy(layout);

    logInfo("Graphics initialized successfully!");
}

void terminateGraphics(void)
{
    destroyBatcher(g_context.batcher);

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

void beginBatch(void) { startBatcher(&g_context.batcher); }
void flushBatch(void) { flushBatcher(&g_context.batcher); }
void endBatch(void)   { endBatcher(&g_context.batcher);   }

void drawQuad(Vec2 pos, Vec2 size, F32 rotation, Vec3 color)
{
    if (g_context.batcher.quad_count == g_context.batcher.max_quads) {
        endBatch();
        flushBatch();
        beginBatch();
    }

    Vertex *buffer_pointer = g_context.batcher.quad_pointer;

    // Bottom left
    Vec2 bl = vec2(-0.5f, -0.5f);
    bl = vec2Rot(bl, rotation);
    bl = vec2Mul(bl, size);
    bl = vec2Add(bl, pos);
    buffer_pointer->position = bl;
    buffer_pointer->color = color;
    buffer_pointer++;

    // Bottom right
    Vec2 br = vec2( 0.5f, -0.5f);
    br = vec2Rot(br, rotation);
    br = vec2Mul(br, size);
    br = vec2Add(br, pos);
    buffer_pointer->position = br;
    buffer_pointer->color = color;
    buffer_pointer++;
    
    // Top left
    Vec2 tl = vec2(-0.5f,  0.5f);
    tl = vec2Rot(tl, rotation);
    tl = vec2Mul(tl, size);
    tl = vec2Add(tl, pos);
    buffer_pointer->position = tl;
    buffer_pointer->color = color;
    buffer_pointer++;
    
    // Top right
    Vec2 tr = vec2( 0.5f,  0.5f);
    tr = vec2Rot(tr, rotation);
    tr = vec2Mul(tr, size);
    tr = vec2Add(tr, pos);
    buffer_pointer->position = tr;
    buffer_pointer->color = color;
    buffer_pointer++;

    g_context.batcher.quad_count++;
    g_context.batcher.quad_pointer = buffer_pointer;
}
