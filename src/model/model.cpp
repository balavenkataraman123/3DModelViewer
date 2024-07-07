//
// Created by Gianni on 1/07/2024.
//

#include "model.hpp"


static constexpr uint32_t import_flags
{
    aiProcess_CalcTangentSpace |
    aiProcess_JoinIdenticalVertices |
    aiProcess_Triangulate |
    aiProcess_RemoveComponent |
    aiProcess_GenNormals |
    aiProcess_OptimizeMeshes |
    aiProcess_OptimizeGraph |
    aiProcess_FlipUVs |
    aiProcess_PreTransformVertices |
    aiProcess_RemoveRedundantMaterials |
    aiProcess_SortByPType
};

static constexpr int remove_components
{
    aiComponent_BONEWEIGHTS |
    aiComponent_ANIMATIONS |
    aiComponent_LIGHTS |
    aiComponent_CAMERAS
};

static constexpr int remove_primitives
{
    aiPrimitiveType_POINT |
    aiPrimitiveType_LINE
};


Model::Model(const std::string& filename) : Model()
{
    import(filename);
}

void Model::import(const std::string& filename)
{
    clear();

    m_directory = filename.substr(0, filename.find_last_of('/') + 1);
    m_model_name = filename.substr(filename.find_last_of('/') + 1);

    std::cout << "ModelLoader: Loading model " << m_model_name << '\n';

    Assimp::Importer importer;
    importer.SetPropertyInteger(AI_CONFIG_PP_RVC_FLAGS, remove_components);
    importer.SetPropertyInteger(AI_CONFIG_PP_SBP_REMOVE, remove_primitives);
    importer.SetPropertyBool(AI_CONFIG_PP_PTV_NORMALIZE, true);

    const aiScene* scene = importer.ReadFile(m_directory + m_model_name, import_flags);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cout << "\033[31mModelLoader: Failed to load " << m_directory + m_model_name << "\033[0m\n";
    }
    else
    {
        process_node(scene->mRootNode, scene);
    }

    std::cout << "ModelLoader: Finished loading " << m_model_name << '\n';
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

    for (size_t i = 0; i < vertex_count; ++i)
    {
        Vertex vertex{};

        vertex.position = *reinterpret_cast<glm::vec3*>(&mesh->mVertices[i]);
        vertex.normal = *reinterpret_cast<glm::vec3*>(&mesh->mNormals[i]);

        if (mesh->HasVertexColors(0))
        {
            vertex.color = *reinterpret_cast<glm::vec3*>(&mesh->mColors[0][i]);
        }
        else
        {
            vertex.color = glm::vec3(0.5f);
        }

        if (mesh->HasTangentsAndBitangents())
        {
            vertex.tangent = *reinterpret_cast<glm::vec3*>(&mesh->mTangents[i]);
            vertex.bitangent = *reinterpret_cast<glm::vec3*>(&mesh->mBitangents[i]);
        }

        if (mesh->HasTextureCoords(0))
        {
            vertex.tex_coords = *reinterpret_cast<glm::vec2*>(&mesh->mTextureCoords[0][i]);
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

    textures[aiTextureType_DIFFUSE] = get_tex_type(material, aiTextureType_DIFFUSE);
    textures[aiTextureType_SPECULAR] = get_tex_type(material, aiTextureType_SPECULAR);
    textures[aiTextureType_HEIGHT] = get_tex_type(material, aiTextureType_HEIGHT);

    std::string mesh_name = mesh->mName.C_Str();

    if (!textures.at(aiTextureType_DIFFUSE))
    {
        std::cout << "\033[31mModelLoader: No diffuse map for [model: "
                  << m_model_name << ", mesh: " << mesh_name << "]\033[0m\n";
    }

    if (!textures.at(aiTextureType_SPECULAR))
    {
        std::cout << "\033[31mModelLoader: No specular map for [model: "
                  << m_model_name << ", mesh: " << mesh_name << "]\033[0m\n";
    }

    if (!textures.at(aiTextureType_HEIGHT))
    {
        std::cout << "\033[31mModelLoader: No normal map for [model: "
                  << m_model_name << ", mesh: " << mesh_name << "]\033[0m\n";
    }

    return textures;
}

std::shared_ptr<Texture2D> Model::get_tex_type(aiMaterial *material, aiTextureType type)
{
    auto load_texture_safe = [] (const char* filename) -> std::shared_ptr<Texture2D>
    {
        std::shared_ptr<Texture2D> texture;

        try
        {
            texture = std::make_shared<Texture2D>(filename);
        }
        catch (const std::exception&)
        {
            std::cout << "\033[31mModelLoader: Failed to load texture " << filename << "\033[0m\n";
        }

        return texture;
    };

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
            std::shared_ptr<Texture2D> mesh_texture = load_texture_safe(path.c_str());
            m_loaded_textures[path] = mesh_texture;
            return mesh_texture;
        }
    }

    return nullptr;
}

void Model::clear()
{
    std::vector<Mesh>().swap(m_meshes);
    std::unordered_map<std::string, std::shared_ptr<Texture2D>>().swap(m_loaded_textures);
    std::string().swap(m_directory);
    std::string().swap(m_model_name);
}
