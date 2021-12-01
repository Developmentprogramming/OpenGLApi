//
// Created by aeternum on 7/24/21.
//

#ifndef OPENGLAPI_LIGHT_H
#define OPENGLAPI_LIGHT_H

#include <glm/glm.hpp>
#include "Shader.h"

struct Light
{
public:
    Light(const std::string& uniform_name, glm::vec4 ambient, glm::vec4 diffuse, glm::vec4 specular);

    glm::vec4 &GetAmbient();
    glm::vec4 &GetDiffuse();
    glm::vec4 &GetSpecular();

    virtual void Render(Shader shader);

protected:
    glm::vec4 m_Ambient;
    glm::vec4 m_Diffuse;
    glm::vec4 m_Specular;
    std::string m_UniformName;
};

struct PointLight : public Light
{
public:
    PointLight(const std::string& uniform_name, glm::vec3 position, glm::vec4 ambient, glm::vec4 diffuse, glm::vec4 specular, float k0 = 1.0f, float k1 = 0.07f, float k2 = 0.032f);

    void Render(Shader shader) override;
    glm::vec3 &GetPos();

protected:
    glm::vec3 m_Position;
    float m_K0, m_K1, m_K2;
};

class DirLight : public Light
{
public:
    DirLight(const std::string& uniform_name, glm::vec3 direction, glm::vec4 ambient, glm::vec4 diffuse, glm::vec4 specular);

    void Render(Shader shader) override;

protected:
    glm::vec3 m_Direction;
};

#endif //OPENGLAPI_LIGHT_H
