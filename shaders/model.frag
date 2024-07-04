#version 460 core

in vec3 v_frag_pos;
in vec2 v_tex_coords;
in mat3 v_tbn_mat;

out vec4 color;

uniform vec3 u_dir_light_dir;
uniform vec3 u_view_pos;
uniform float u_kl;
uniform float u_kq;

uniform sampler2D u_diffuse_map;
uniform sampler2D u_specular_map;
uniform sampler2D u_normal_map;

#define light_color vec3(1.f, 1.f, 1.f)
#define ambient_intensity 0.2f
#define shininess 32.f


vec3 calculate_light(vec3 diff_sample, vec3 spec_sample, vec3 norm, vec3 light_dir)
{
    // ambient
    vec3 ambient = light_color * diff_sample * ambient_intensity;

    // diffuse
    float cos_theta_diff = max(dot(-light_dir, norm), 0.f);
    vec3 diffuse = light_color * diff_sample * cos_theta_diff;

    // specular
    vec3 reflected_dir = reflect(light_dir, norm);
    vec3 view_dir = normalize(u_view_pos - v_frag_pos);
    float cos_theta_spec = max(dot(view_dir, reflected_dir), 0.f);
    vec3 specular = light_color * spec_sample * pow(cos_theta_spec, shininess);

    return ambient + diffuse + specular;
}

float attenuation()
{
    float distance = length(u_view_pos - v_frag_pos);
    return 1.f / (1.f + u_kl * distance + u_kq * pow(distance, 2.f));
}

void main()
{
    vec3 diffuse_sample = texture(u_diffuse_map, v_tex_coords).rgb;
    vec3 specular_sample = texture(u_specular_map, v_tex_coords).rgb;
    vec3 normal_sample = texture(u_normal_map, v_tex_coords).rgb * 2.f - 1.f;
    vec3 normal = normalize(v_tbn_mat * normal_sample);
    vec3 point_light_dir = normalize(v_frag_pos - u_view_pos);

    vec3 dir_light_value = calculate_light(diffuse_sample, specular_sample, normal, normalize(u_dir_light_dir));
    vec3 point_light_value = calculate_light(diffuse_sample, specular_sample, normal, point_light_dir) * attenuation();

    color = vec4(dir_light_value + point_light_value, 1.f);
}
