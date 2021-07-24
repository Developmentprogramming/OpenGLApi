//
// Created by aeternum on 7/21/21.
//

#include <iostream>
#include "Mesh.h"

std::vector<Vertex> Vertex::CreateVertices(float *vertices, int noVertices)
{
    std::vector<Vertex> ret(noVertices);

    constexpr int stride = sizeof(Vertex) / sizeof(float);
    for (int i = 0; i < noVertices; i++)
    {
        ret[i].m_Pos = glm::vec3(
                vertices[i * stride + 0],
                vertices[i * stride + 1],
                vertices[i * stride + 2]
                );

        ret[i].m_TexCoord = glm::vec2(
                vertices[i * stride + 3],
                vertices[i * stride + 4]
                );
    }

    return ret;
}

Mesh::Mesh()
{
}

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures)
    : m_Vertices(std::move(vertices)), m_Indices(std::move(indices)), m_Textures(std::move(textures))
{
    glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);

    glGenBuffers(1, &m_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, m_Vertices.size() * sizeof(Vertex), &m_Vertices[0], GL_STATIC_DRAW);

    // Layout
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));

    glGenBuffers(1, &m_EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Indices.size() * sizeof(unsigned int), &m_Indices[0], GL_STATIC_DRAW);

    glBindVertexArray(0);
}

void Mesh::Render(Shader shader)
{
    for (int i = 0; i < m_Textures.size(); i++)
    {
        shader.SetInt(m_Textures[i].GetTextureName(), m_Textures[i].GetId());
        m_Textures[i].Bind(i);
    }

    glBindVertexArray(m_VAO);
    glDrawElements(GL_TRIANGLES, m_Indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    glActiveTexture(GL_TEXTURE0);
}

void Mesh::CleanUp()
{
    glDeleteVertexArrays(1, &m_VAO);
    glDeleteBuffers(1, &m_VBO);
    glDeleteBuffers(1, &m_EBO);
}
