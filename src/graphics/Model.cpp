//
// Created by aeternum on 7/21/21.
//

#include "Model.h"

Model::Model()
{
}

void Model::Render(Shader shader)
{
    for (auto& mesh : m_Meshes)
        mesh.Render(shader);
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
