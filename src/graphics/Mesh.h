//
// Created by aeternum on 7/21/21.
//

#ifndef OPENGLAPI_MESH_H
#define OPENGLAPI_MESH_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vector>

#include "Texture.h"
#include "Shader.h"

struct Vertex
{
    glm::vec3 m_Pos;
    glm::vec2 m_TexCoord;

    static std::vector<Vertex> CreateVertices(float *vertices, int noVertices);
};

class Mesh
{
public:
    Mesh();
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);

    void Render(Shader shader);
    void CleanUp();

protected:
    std::vector<Vertex> m_Vertices;
    std::vector<unsigned int> m_Indices;
    std::vector<Texture> m_Textures;

private:
    unsigned int m_VAO, m_VBO, m_EBO;
};

#endif //OPENGLAPI_MESH_H
