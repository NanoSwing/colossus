#version 460 core
out vec4 FragColor;

in vec2 f_uv;

uniform sampler2D screen_texture;

void main()
{
    FragColor = texture(screen_texture, f_uv);
    // FragColor = vec4(f_uv, 0.0, 1.0);
}
