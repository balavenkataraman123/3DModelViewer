#version 460 core

in vec3 v_frag_pos;
in vec3 v_normal;
in vec2 v_tex_coords;

out vec4 color;

uniform vec3 u_view_pos;
uniform vec3 u_directional_light_dir;
uniform vec3 u_point_light_pos;
uniform float u_kl;
uniform float u_kq;
uniform sampler2D u_diffuse_map;
uniform sampler2D u_specular_map;

#define light_color vec3(1.f, 1.f, 1.f)
#define ambient_intensity 0.2f


vec3 calculate_dir_light(vec3 diffuse_sample, vec3 specular_sample, vec3 normal)
{
    vec3 light_dir = normalize(u_directional_light_dir);

    // ambient
    vec3 ambient = light_color * diffuse_sample * ambient_intensity;

    // diffuse
    float cos_theta_diff = max(dot(-light_dir, normal), 0.f);
    vec3 diffuse = light_color * diffuse_sample * cos_theta_diff;

    // specular
    vec3 reflected_dir = reflect(light_dir, normal);
    vec3 view_dir = normalize(u_view_pos - v_frag_pos);
    float cos_theta_spec = max(dot(view_dir, reflected_dir), 0.f);
    vec3 specular = light_color * specular_sample * pow(cos_theta_spec, 32.f);

    return ambient + diffuse + specular;
}


vec3 calculate_point_light(vec3 diffuse_sample, vec3 specular_sample, vec3 normal)
{
    vec3 light_dir = normalize(v_frag_pos - u_point_light_pos);

    // ambient
    vec3 ambient = light_color * diffuse_sample * ambient_intensity;

    // diffuse
    float cos_theta_diff = max(dot(-light_dir, normal), 0.f);
    vec3 diffuse = light_color * diffuse_sample * cos_theta_diff;

    // specular
    vec3 reflected_dir = reflect(light_dir, normal);
    vec3 view_dir = normalize(u_view_pos - v_frag_pos);
    float cos_theta_spec = max(dot(view_dir, reflected_dir), 0.f);
    vec3 specular = light_color * specular_sample * pow(cos_theta_spec, 32.f);

    // attenuation
    float distance = length(u_point_light_pos - v_frag_pos);
    float attenuation = 1.f / (1.f + u_kl * distance + u_kq * pow(distance, 2.f));

    return (ambient + diffuse + specular) * attenuation;
}


void main()
{
    vec3 diffuse_sample = texture(u_diffuse_map, v_tex_coords).rgb;
    vec3 specular_sample = texture(u_specular_map, v_tex_coords).rgb;
    vec3 normal = normalize(v_normal);

    color = vec4(calculate_dir_light(diffuse_sample, specular_sample, normal), 1.f);
    color += vec4(calculate_point_light(diffuse_sample, specular_sample, normal), 1.f);
}
