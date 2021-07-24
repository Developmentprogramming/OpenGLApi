//
// Created by aeternum on 7/21/21.
//

#ifndef OPENGLAPI_CUBE_H
#define OPENGLAPI_CUBE_H

#include "../Model.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Cube : public Model
{
public:
    Cube(glm::vec3 pos, glm::vec3 size)
        : m_Pos(pos), m_Size(size)
    {
    }

    void Init() override
    {
        int noVertices = 36;

        float vertices[] =
                {
                        -0.5f, -0.5f, -0.5f,	0.0f, 0.0f,
                         0.5f, -0.5f, -0.5f,	1.0f, 0.0f,
                         0.5f,  0.5f, -0.5f,	1.0f, 1.0f,
                         0.5f,  0.5f, -0.5f,	1.0f, 1.0f,
                        -0.5f,  0.5f, -0.5f,	0.0f, 1.0f,
                        -0.5f, -0.5f, -0.5f,	0.0f, 0.0f,

                        -0.5f, -0.5f,  0.5f,	0.0f, 0.0f,
                         0.5f, -0.5f,  0.5f,	1.0f, 0.0f,
                         0.5f,  0.5f,  0.5f,	1.0f, 1.0f,
                         0.5f,  0.5f,  0.5f,	1.0f, 1.0f,
                        -0.5f,  0.5f,  0.5f,	0.0f, 1.0f,
                        -0.5f, -0.5f,  0.5f,	0.0f, 0.0f,

                        -0.5f,  0.5f,  0.5f,	1.0f, 0.0f,
                        -0.5f,  0.5f, -0.5f,	1.0f, 1.0f,
                        -0.5f, -0.5f, -0.5f,	0.0f, 1.0f,
                        -0.5f, -0.5f, -0.5f,	0.0f, 1.0f,
                        -0.5f, -0.5f,  0.5f,	0.0f, 0.0f,
                        -0.5f,  0.5f,  0.5f,	1.0f, 0.0f,

                         0.5f,  0.5f,  0.5f,	1.0f, 0.0f,
                         0.5f,  0.5f, -0.5f,	1.0f, 1.0f,
                         0.5f, -0.5f, -0.5f,	0.0f, 1.0f,
                         0.5f, -0.5f, -0.5f,	0.0f, 1.0f,
                         0.5f, -0.5f,  0.5f,	0.0f, 0.0f,
                         0.5f,  0.5f,  0.5f,	1.0f, 0.0f,

                        -0.5f, -0.5f, -0.5f,	0.0f, 1.0f,
                         0.5f, -0.5f, -0.5f,	1.0f, 1.0f,
                         0.5f, -0.5f,  0.5f,	1.0f, 0.0f,
                         0.5f, -0.5f,  0.5f,	1.0f, 0.0f,
                        -0.5f, -0.5f,  0.5f,	0.0f, 0.0f,
                        -0.5f, -0.5f, -0.5f,	0.0f, 1.0f,

                        -0.5f,  0.5f, -0.5f,	0.0f, 1.0f,
                         0.5f,  0.5f, -0.5f,	1.0f, 1.0f,
                         0.5f,  0.5f,  0.5f,	1.0f, 0.0f,
                         0.5f,  0.5f,  0.5f,	1.0f, 0.0f,
                        -0.5f,  0.5f,  0.5f,	0.0f, 0.0f,
                        -0.5f,  0.5f, -0.5f,	0.0f, 1.0f
                };

        std::vector<unsigned int> indices(noVertices);
        for (int i = 0; i < noVertices; ++i)
            indices[i] = i;

        Texture aeternum_logo("/home/aeternum/CLionProjects/OpenGLApi/assets/textures/AeternumLogo.png", "u_Texture");

        m_Meshes.push_back(Mesh(Vertex::CreateVertices(vertices, noVertices), indices, { aeternum_logo }));
    }

    void Render(Shader shader) override
    {
        glm::mat4 model = glm::mat4(1.0f);

        model = glm::translate(model, m_Pos);
        model = glm::scale(model, m_Size);
        model = glm::rotate(model, glm::radians((float)glfwGetTime() * -55.0f), glm::vec3(1.0f, 5.0f, 1.0f));

        shader.SetMat4("model", model);

        Model::Render(shader);
    }

protected:
    glm::vec3 m_Pos, m_Size;
};

#endif //OPENGLAPI_CUBE_H
