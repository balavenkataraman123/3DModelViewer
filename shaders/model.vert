#version 460 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 tex_coords;

out vec3 v_frag_pos;
out vec3 v_normal;
out vec2 v_tex_coords;

uniform mat4 u_proj;
uniform mat4 u_model;

void main()
{
    gl_Position = u_proj * u_model * vec4(position, 1.f);

    v_frag_pos = vec3(u_model * vec4(position, 1.f));
    v_normal = mat3(transpose(inverse(u_model))) * normal;
    v_tex_coords = tex_coords;
}
