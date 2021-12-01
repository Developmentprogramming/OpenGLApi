//
// Created by aeternum on 7/21/21.
//

#ifndef OPENGLAPI_MODEL_H
#define OPENGLAPI_MODEL_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <assimp/scene.h>

#include "Mesh.h"
#include "../physics/RigidBody.h"

class Model : public RigidBody
{
public:
    Model(glm::vec3 pos, glm::vec3 size, bool noTex = false, glm::mat4 model = glm::mat4(1.0f));

    virtual void Render(Shader shader, float dt);
    void LoadModel(const std::string& path);
    void CleanUp();

    void Rotate(float angle, glm::vec3 v);

    std::vector<Mesh>& GetMeshes();
    void SetSize(glm::vec3 size);

protected:
    std::vector<Mesh> m_Meshes;
    glm::vec3 m_Size;

    // Model matrix
    glm::mat4 m_Model;
    glm::vec3 m_RotationVector;
    float m_Angle;

    std::string m_Directory;
    std::vector<Texture> m_LoadedTextures;
    bool m_NoTex;

    /* For Assimp Library */
    void ProcessNode(aiNode* node, const aiScene* scene);
    Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
    std::vector<Texture> LoadTextures(aiMaterial* material, aiTextureType type);
};


#endif //OPENGLAPI_MODEL_H
