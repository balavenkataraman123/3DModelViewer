#version 460 core

in vec3 v_frag_pos;
in vec3 v_normal;
in vec2 v_tex_coords;
in mat3 v_tbn_mat;

out vec4 color;

uniform int u_has_diffuse;
uniform int u_has_specular;
uniform int u_has_normal;
uniform vec3 u_view_pos;
uniform sampler2D u_diffuse_map;
uniform sampler2D u_specular_map;
uniform sampler2D u_normal_map;

void main()
{
    vec3 diffuse_color;
    vec3 specular_color;
    vec3 normal;

    if (u_has_diffuse == 1)
    {
        diffuse_color = texture(u_diffuse_map, v_tex_coords).rgb;
    }
    else
    {
        diffuse_color = vec3(0.5f);
    }

    if (u_has_specular == 1)
    {
        specular_color = texture(u_specular_map, v_tex_coords).rgb;
    }
    else
    {
        specular_color = vec3(0.5f);
    }

    if (u_has_normal == 1)
    {
        vec3 normal_sample = texture(u_normal_map, v_tex_coords).rgb * 2.f - 1.f;
        normal = normalize(v_tbn_mat * normal_sample);
    }
    else
    {
        normal = normalize(v_normal);
    }

    vec3 light_dir = normalize(v_frag_pos - u_view_pos);

    // ambient
    vec3 ambient = diffuse_color * 0.2f;

    // diffuse
    float cos_theta_diff = max(dot(-light_dir, normal), 0.f);
    vec3 diffuse = diffuse_color * cos_theta_diff;

    // specular
    vec3 reflected_dir = reflect(light_dir, normal);
    vec3 view_dir = normalize(u_view_pos - v_frag_pos);
    float cos_theta_spec = max(dot(view_dir, reflected_dir), 0.f);
    vec3 specular = specular_color * pow(cos_theta_spec, 128.f);

    color = vec4(ambient + diffuse + specular, 1.f);
}
