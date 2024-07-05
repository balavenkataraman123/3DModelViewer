//
// Created by Gianni on 1/07/2024.
//

#ifndef INC_3DMODELVIEWER_MODEL_HPP
#define INC_3DMODELVIEWER_MODEL_HPP

#include <string>
#include <iostream>
#include <unordered_map>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "mesh.hpp"


class Model
{
public:
    Model() = default;
    Model(const std::string& filename);

    void import(const std::string& filename);
    void render(const Shader& shader) const;

private:
    void import_impl();
    void clear();

    void process_node(aiNode* node, const aiScene* scene);
    void process_mesh(aiMesh* mesh, const aiScene* scene);

    std::vector<Vertex> get_vertices(aiMesh* mesh);
    std::vector<uint32_t> get_indices(aiMesh* mesh);
    mesh_textures_t get_textures(aiMesh* mesh, const aiScene* scene);

private:
    std::vector<Mesh> m_meshes;
    std::unordered_map<std::string, std::shared_ptr<Texture2D>> m_loaded_textures;
    std::string m_directory;
    std::string m_model_name;
};


#endif //INC_3DMODELVIEWER_MODEL_HPP
