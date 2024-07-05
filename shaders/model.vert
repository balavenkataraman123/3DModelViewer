#version 460 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 tangent;
layout (location = 3) in vec3 bitangent;
layout (location = 4) in vec2 tex_coords;

out vec3 v_frag_pos;
out vec3 v_normal;
out vec2 v_tex_coords;
out mat3 v_tbn_mat;

uniform int u_has_normal;
uniform mat4 u_proj_view;
uniform mat4 u_model;

void main()
{
    gl_Position = u_proj_view * u_model * vec4(position, 1.f);

    v_frag_pos = vec3(u_model * vec4(position, 1.f));
    v_tex_coords = tex_coords;

    mat3 normal_mat = mat3(transpose(inverse(u_model)));
    v_normal = normal_mat * normal;

    if (u_has_normal == 1)
    {
        vec3 t = normalize(normal_mat * tangent);
        vec3 b = normalize(normal_mat * bitangent);
        vec3 n = normalize(normal_mat * normal);
        v_tbn_mat = mat3(t, b, n);
    }
}
