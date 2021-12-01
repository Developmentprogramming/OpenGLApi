//
// Created by aeternum on 7/21/21.
//

#include <iostream>
#include <utility>
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

        ret[i].m_Normal = glm::vec3(
                vertices[i * stride + 3],
                vertices[i * stride + 4],
                vertices[i * stride + 5]
                );

        ret[i].m_TexCoord = glm::vec2(
                vertices[i * stride + 6],
                vertices[i * stride + 7]
                );
    }

    return ret;
}

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures)
    : Mesh(std::move(vertices), std::move(indices), std::move(textures), false, aiColor4D(1.0f), aiColor4D(1.0f))
{
}

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, aiColor4D diffColor, aiColor4D specColor)
    : Mesh(std::move(vertices), std::move(indices), {}, true, diffColor, specColor)
{
}

void Mesh::Render(Shader shader, const std::string& uniform_material)
{
    if (m_NoTex)
    {
        shader.Set4Float(uniform_material + ".diffuse", m_DiffColor);
        shader.Set4Float(uniform_material + ".specular", m_SpecColor);
        shader.SetInt("noTex", 1);
    }
    else
    {
        shader.SetInt("noTex", 0);

        unsigned int diffIdx = 0;
        unsigned int specIdx = 0;
        for (int i = 0; i < m_Textures.size(); i++)
        {
            m_Textures[i].Bind(i);

            std::string name;
            switch (m_Textures[i].GetType())
            {

                case aiTextureType_DIFFUSE:
                    name = "diffuse" + std::to_string(diffIdx++);
                    break;
                case aiTextureType_SPECULAR:
                    name = "specular" + std::to_string(specIdx++);
                    break;

                default:
                    break;
            }

            m_Textures[i].SetTextureName(name);
            shader.SetInt(m_Textures[i].GetTextureName(), i);
        }
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

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures, bool noTex, aiColor4D diffColor, aiColor4D specColor)
    : m_Vertices(std::move(vertices)), m_Indices(std::move(indices)), m_Textures(std::move(textures)),
    m_NoTex(noTex), m_DiffColor(diffColor), m_SpecColor(specColor)
{
    glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);

    glGenBuffers(1, &m_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, m_Vertices.size() * sizeof(Vertex), &m_Vertices[0], GL_STATIC_DRAW);

    glGenBuffers(1, &m_EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Indices.size() * sizeof(unsigned int), &m_Indices[0], GL_STATIC_DRAW);

    // Layout
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(6 * sizeof(float)));

    glBindVertexArray(0);
}
