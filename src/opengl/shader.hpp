//
// Created by Gianni on 30/06/2024.
//

#ifndef INC_3DMODELVIEWER_SHADER_HPP
#define INC_3DMODELVIEWER_SHADER_HPP

#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>


class Shader
{
public:
    Shader();
    Shader(const char* vs_file, const char* fs_file);
    ~Shader();

    Shader(Shader&& other) noexcept;
    Shader& operator=(Shader&& other) noexcept;

    Shader(const Shader&) = delete;
    Shader& operator=(const Shader&) = delete;

    void bind() const;
    void unbind() const;

    void set_int(const char* name, int v0) const;
    void set_float(const char* name, float v0) const;
    void set_float2(const char* name, float v0 , float v1) const;
    void set_float2(const char* name, const glm::vec2& vec2) const;
    void set_float3(const char* name, float v0, float v1, float v2) const;
    void set_float3(const char* name, const glm::vec3& vec3) const;
    void set_float4(const char* name, float v0, float v1, float v2, float v3) const;
    void set_float4(const char* name, const glm::vec4& vec4) const;
    void set_mat4(const char* name, const glm::mat4& matrix) const;

    uint32_t id() const;

private:
    std::string parse_shader(const char* file_name);
    uint32_t compile_shader(uint32_t type, const char* source);
    int get_uniform_location(const char* name) const;

private:
    uint32_t m_renderer_id;
    mutable std::unordered_map<const char*, int> m_uniform_location_cache;
};


#endif //INC_3DMODELVIEWER_SHADER_HPP
