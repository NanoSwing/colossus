#version 460 core
out vec4 FragColor;

in vec4 color;
in float texture_id;
in vec2 texture_coords;

uniform sampler2D textures[32];

void main()
{
    int index = int(texture_id);
    FragColor = texture(textures[index], texture_coords) * color;
}
