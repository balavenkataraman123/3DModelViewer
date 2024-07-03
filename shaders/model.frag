#version 460 core

in vec2 v_tex_coords;

out vec4 color;

uniform sampler2D u_diffuse_map;

void main()
{
    color = texture(u_diffuse_map, v_tex_coords);
}
