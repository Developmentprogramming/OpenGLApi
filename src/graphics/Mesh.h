//
// Created by aeternum on 7/21/21.
//

#ifndef OPENGLAPI_MESH_H
#define OPENGLAPI_MESH_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vector>
#include <assimp/scene.h>

#include "Texture.h"
#include "Shader.h"

struct Vertex
{
    glm::vec3 m_Pos;
    glm::vec3 m_Normal;
    glm::vec2 m_TexCoord;

    static std::vector<Vertex> CreateVertices(float *vertices, int noVertices);
};

class Mesh
{
public:
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, aiColor4D diffColor, aiColor4D specColor);

    void Render(Shader shader, const std::string& uniform_material = "material");
    void CleanUp();

protected:
    std::vector<Vertex> m_Vertices;
    std::vector<unsigned int> m_Indices;
    std::vector<Texture> m_Textures;

    aiColor4D m_DiffColor, m_SpecColor;
    bool m_NoTex;

private:
    unsigned int m_VAO, m_VBO, m_EBO;

    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures, bool noTex, aiColor4D diffColor, aiColor4D specColor);
};

#endif //OPENGLAPI_MESH_H
