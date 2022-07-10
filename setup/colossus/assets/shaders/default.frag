#version 460 core
out vec4 FragColor;

in vec2 f_uv;
in vec4 f_color;
in float f_texture_index;

uniform sampler2D textures[32];

void main()
{
    int i = int(f_texture_index);

    FragColor = texture(textures[i], f_uv) * f_color;
}
