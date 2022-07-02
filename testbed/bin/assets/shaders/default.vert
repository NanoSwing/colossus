#version 460 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec4 aColor;
layout (location = 2) in float aTexture_id;
layout (location = 3) in vec2 aTexture_coords;

out vec4 color;
out float texture_id;
out vec2 texture_coords;

uniform mat4 projection;

void main()
{
    color = aColor;
    texture_id = aTexture_id;
    texture_coords = aTexture_coords;
    gl_Position = projection * vec4(aPos, 0.0, 1.0);
}
