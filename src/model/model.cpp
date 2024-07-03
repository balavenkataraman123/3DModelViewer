//
// Created by Gianni on 1/07/2024.
//

#include "model.hpp"

// todo: check pre transform vertex
static constexpr uint32_t import_flags
{
    aiProcess_CalcTangentSpace |
    aiProcess_JoinIdenticalVertices |
    aiProcess_Triangulate |
    aiProcess_RemoveComponent |
    aiProcess_GenNormals |
    aiProcess_OptimizeMeshes |
    aiProcess_OptimizeGraph |
    aiProcess_FlipUVs
};

static constexpr int remove_components
{
    aiComponent_COLORS |
    aiComponent_BONEWEIGHTS |
    aiComponent_ANIMATIONS |
    aiComponent_LIGHTS |
    aiComponent_CAMERAS
};


Model::Model(const std::string& filename)
{
    Assimp::Importer importer;
    importer.SetPropertyInteger(AI_CONFIG_PP_RVC_FLAGS, remove_components);

    const aiScene* scene = importer.ReadFile(filename, import_flags);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        throw std::runtime_error("Model::Model: " + std::string(importer.GetErrorString()));
    }

    m_directory = filename.substr(0, filename.find_last_of('/') + 1);

    process_node(scene->mRootNode, scene);
}


void Model::render(const Shader &shader) const
{
    for (const auto& mesh : m_meshes)
    {
        mesh.render(shader);
    }
}

void Model::process_node(aiNode *node, const aiScene *scene)
{
    for (uint32_t i = 0; i < node->mNumMeshes; ++i)
    {
        uint32_t mesh_index = node->mMeshes[i];
        aiMesh* mesh = scene->mMeshes[mesh_index];
        process_mesh(mesh, scene);
    }

    for (uint32_t i = 0; i < node->mNumChildren; ++i)
    {
        process_node(node->mChildren[i], scene);
    }
}

void Model::process_mesh(aiMesh *mesh, const aiScene *scene)
{
    std::vector<Vertex> vertices = get_vertices(mesh);
    std::vector<uint32_t> indices = get_indices(mesh);
    mesh_textures_t textures = get_textures(mesh, scene);

    m_meshes.emplace_back(vertices, indices, std::move(textures));
}

std::vector<Vertex> Model::get_vertices(aiMesh *mesh)
{
    const size_t vertex_count = mesh->mNumVertices;

    std::vector<Vertex> vertices;
    vertices.reserve(vertex_count);

    for (uint32_t i = 0; i < vertex_count; ++i)
    {
        Vertex vertex
        {
            *reinterpret_cast<glm::vec3*>(&mesh->mVertices[i]),
            *reinterpret_cast<glm::vec3*>(&mesh->mNormals[i])
        };

        if (mesh->HasTextureCoords(0))
        {
            vertex.tex_coords.x = mesh->mTextureCoords[0][i].x;
            vertex.tex_coords.y = mesh->mTextureCoords[0][i].y;
        }

        vertices.push_back(std::move(vertex));
    }

    return vertices;
}

std::vector<uint32_t> Model::get_indices(aiMesh *mesh)
{
    std::vector<uint32_t> indices;
    indices.reserve(mesh->mNumFaces * 3);

    for (uint32_t i = 0, face_count = mesh->mNumFaces; i < face_count; ++i)
    {
        const aiFace& face = mesh->mFaces[i];
        indices.insert(indices.end(), face.mIndices, face.mIndices + face.mNumIndices);
    }

    return indices;
}

mesh_textures_t Model::get_textures(aiMesh *mesh, const aiScene *scene)
{
    mesh_textures_t textures;
    aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

    static auto get_tex_type = [&, this] (aiTextureType type) -> std::shared_ptr<Texture2D>
    {
        aiString filename;

        if (material->GetTextureCount(type))
        {
            material->GetTexture(type, 0, &filename);

            std::string path = m_directory + std::string(filename.C_Str());

            if (m_loaded_textures.contains(path))
            {
               return m_loaded_textures.at(path);
            }
            else
            {
                auto mesh_texture = std::make_shared<Texture2D>(path.c_str());
                m_loaded_textures[path] = mesh_texture;
                return mesh_texture;
            }
        }

        return nullptr;
    };

    textures[aiTextureType_AMBIENT] = get_tex_type(aiTextureType_AMBIENT);
    textures[aiTextureType_DIFFUSE] = get_tex_type(aiTextureType_DIFFUSE);
    textures[aiTextureType_SPECULAR] = get_tex_type(aiTextureType_SPECULAR);
    textures[aiTextureType_SHININESS] = get_tex_type(aiTextureType_SHININESS);
    textures[aiTextureType_HEIGHT] = get_tex_type(aiTextureType_HEIGHT);

    return textures;
}
