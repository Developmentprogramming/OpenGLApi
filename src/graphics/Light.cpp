//
// Created by aeternum on 7/24/21.
//

#include "Light.h"

Light::Light(const std::string& uniform_name, glm::vec4 ambient, glm::vec4 diffuse, glm::vec4 specular)
    : m_UniformName(uniform_name), m_Ambient(ambient), m_Diffuse(diffuse), m_Specular(specular)
{
}

glm::vec4 &Light::GetAmbient()
{
    return m_Ambient;
}

glm::vec4 &Light::GetDiffuse()
{
    return m_Diffuse;
}

glm::vec4 &Light::GetSpecular()
{
    return m_Specular;
}

void Light::Render(Shader shader)
{
    shader.Set4Float(m_UniformName + ".ambient", m_Ambient);
    shader.Set4Float(m_UniformName + ".diffuse", m_Diffuse);
    shader.Set4Float(m_UniformName + ".specular", m_Specular);
}

PointLight::PointLight(const std::string &uniform_name, glm::vec3 position, glm::vec4 ambient, glm::vec4 diffuse, glm::vec4 specular, float k0, float k1, float k2)
    : m_Position(position), Light(uniform_name, ambient, diffuse, specular), m_K0(k0), m_K1(k1), m_K2(k2)
{
}

void PointLight::Render(Shader shader)
{
    shader.Set3Float(m_UniformName + ".position", m_Position);
    shader.SetFloat(m_UniformName + ".k0", m_K0);
    shader.SetFloat(m_UniformName + ".k1", m_K1);
    shader.SetFloat(m_UniformName + ".k2", m_K2);
    Light::Render(shader);
}

glm::vec3 &PointLight::GetPos()
{
    return m_Position;
}

DirLight::DirLight(const std::string &uniform_name, glm::vec3 direction, glm::vec4 ambient, glm::vec4 diffuse, glm::vec4 specular)
    : Light(uniform_name, ambient, diffuse, specular), m_Direction(direction)
{
}

void DirLight::Render(Shader shader)
{
    shader.Set3Float(m_UniformName + ".direction", m_Direction);

    Light::Render(shader);
}
