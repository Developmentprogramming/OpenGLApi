//
// Created by aeternum on 7/21/21.
//

#include "Model.h"

#include <glm/gtc/matrix_transform.hpp>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <iostream>

Model::Model(glm::vec3 pos, glm::vec3 size, bool noTex, glm::mat4 model)
    : RigidBody(pos), m_Size(size), m_Model(model),
    m_NoTex(noTex), m_Angle(0.0f), m_RotationVector(0.0f)
{
}

void Model::Render(Shader shader, float dt)
{
    this->Update(dt);

    // model rendering order should be Translation, Scale and Rotation
    // or Rotation, Translation and Scale

    m_Model = glm::mat4(1.0f);
    m_Model = glm::translate(m_Model, m_Pos);
    m_Model = glm::scale(m_Model, m_Size);
    if (m_Angle != 0.0f)
    {
        m_Model = glm::rotate(m_Model, m_Angle, m_RotationVector);
        m_Angle = 0.0f;
        m_RotationVector = glm::vec3(0.0f);
    }

    shader.SetMat4("model", m_Model);

    for (auto& mesh : m_Meshes)
        mesh.Render(shader);
}

void Model::LoadModel(const std::string& path)
{
    Assimp::Importer import;
    const aiScene* scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cout << "[Assimp]: Unable to load model(" << path << ")\t" << "Error: " << import.GetErrorString() << std::endl;
        return;
    }

    m_Directory = path.substr(0, path.find_last_of('/'));
    ProcessNode(scene->mRootNode, scene);
}

void Model::CleanUp()
{
    for (auto& mesh : m_Meshes)
        mesh.CleanUp();
}

std::vector<Mesh>& Model::GetMeshes()
{
    return m_Meshes;
}

void Model::SetSize(glm::vec3 size)
{
    m_Size = size;
}

void Model::Rotate(float angle, glm::vec3 v)
{
    m_Angle += angle;
    m_RotationVector += v;
}

void Model::ProcessNode(aiNode* node, const aiScene *scene)
{
    // Process all meshes
    for (int i = 0; i < node->mNumMeshes; ++i)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        m_Meshes.push_back(ProcessMesh(mesh, scene));
    }

    for (int i = 0; i < node->mNumChildren; ++i)
        ProcessNode(node->mChildren[i], scene);
}

Mesh Model::ProcessMesh(aiMesh* mesh, const aiScene *scene)
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    // aiMesh::mVertices to OpenGLApi::Mesh::m_Vertices
    for (int i = 0; i < mesh->mNumVertices; ++i)
    {
        auto texCoord = glm::vec2(0.0f);

        glm::vec3 pos = glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
        glm::vec3 normal = glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);

        if (mesh->mTextureCoords[0])
            texCoord = glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);

        vertices.push_back({ pos, normal, texCoord });
    }

    // aiMesh::mFaces to OpenGLApi::Mesh::m_Indices
    for (int i = 0; i < mesh->mNumFaces; ++i)
    {
        auto face = mesh->mFaces[i];
        for (int j = 0; j < face.mNumIndices; ++j)
            indices.push_back(face.mIndices[j]);
    }

    aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

    if (m_NoTex)
    {
        aiColor4D diffColor(1.0f);
        material->Get(AI_MATKEY_COLOR_DIFFUSE, diffColor);

        aiColor4D specColor(1.0f);
        material->Get(AI_MATKEY_COLOR_SPECULAR, specColor);

        return Mesh(vertices, indices, diffColor, specColor);
    }

    std::vector<Texture> diffMaps = LoadTextures(material, aiTextureType_DIFFUSE);
    textures.insert(textures.end(), diffMaps.begin(), diffMaps.end());

    std::vector<Texture> specMaps = LoadTextures(material, aiTextureType_SPECULAR);
    textures.insert(textures.end(), specMaps.begin(), specMaps.end());

    return Mesh(vertices, indices, textures);
}

std::vector<Texture> Model::LoadTextures(aiMaterial *material, aiTextureType type)
{
    std::vector<Texture> textures;

    for (int i = 0; i < material->GetTextureCount(type); ++i)
    {
        aiString str;
        material->GetTexture(type, i, &str);
        std::cout << "[Assimp Loaded]: " << str.C_Str() << std::endl;

        // Prevent duplicate textures
        bool skip = false;
        for (auto& loadedTexture : m_LoadedTextures)
        {
            if (std::strcmp(loadedTexture.GetPath().data(), str.C_Str()) == 0)
            {
                textures.push_back(loadedTexture);
                skip = true;
                break;
            }
        }

        if (!skip)
        {
            auto& obj = textures.emplace_back((m_Directory + "/" + str.C_Str()), "", type, false);
            m_LoadedTextures.push_back(obj);
        }
    }

    return std::move(textures);
}

