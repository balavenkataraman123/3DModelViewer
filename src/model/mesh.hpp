//
// Created by Gianni on 1/07/2024.
//

#ifndef INC_3DMODELVIEWER_MESH_HPP
#define INC_3DMODELVIEWER_MESH_HPP

#include <vector>
#include <memory>
#include <unordered_map>
#include <assimp/material.h>
#include "../opengl/includes.hpp"


struct Vertex;

using mesh_textures_t = std::unordered_map<aiTextureType, std::shared_ptr<Texture2D>>;

class Mesh
{
public:
    Mesh() = default;
    Mesh(const std::vector<Vertex>& vertices,
         const std::vector<uint32_t>& indices,
         mesh_textures_t&& textures);

    void render(const Shader& shader) const;

private:
    VertexArray m_vao;
    VertexBufferStatic m_vbo;
    IndexBufferStatic m_ibo;
    mesh_textures_t m_textures;
};


struct Vertex
{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 tex_coords;
};


#endif //INC_3DMODELVIEWER_MESH_HPP
