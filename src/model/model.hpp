//
// Created by Gianni on 1/07/2024.
//

#ifndef INC_3DMODELVIEWER_MODEL_HPP
#define INC_3DMODELVIEWER_MODEL_HPP

#include <string>
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

private:
    void process_node(aiNode* node, const aiScene* scene);
    Mesh process_mesh(aiMesh* mesh, const aiScene* scene);

    std::vector<Vertex> get_vertices(aiMesh* mesh);
    std::vector<uint32_t> get_indices(aiMesh* mesh);
    std::vector<Texture2D> get_textures(aiMesh* mesh, const aiScene* scene);

private:
    std::vector<Mesh> m_meshes;
    std::unordered_map<const char*, bool> m_cache;
    std::string m_directory;
};


#endif //INC_3DMODELVIEWER_MODEL_HPP
