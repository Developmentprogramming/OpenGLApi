//
// Created by aeternum on 7/24/21.
//

#ifndef OPENGLAPI_LAMP_H
#define OPENGLAPI_LAMP_H

#include "Cube.h"
#include "../Light.h"

class Lamp : public Cube
{
public:
    Lamp(glm::vec3 lightColor, glm::vec3 pos, glm::vec3 size)
        : m_LightColor(lightColor),
        Cube(pos, size),
        m_Light("pointLight", pos, glm::vec4(glm::vec3(0.05f), 1.0), glm::vec4(glm::vec3(0.8f), 1.0), glm::vec4(1.0))
    {
    }

    void Render(Shader shader, float dt) override
    {
        shader.Set3Float("lightColor", m_LightColor);
        Cube::Render(shader, dt);
    }

    PointLight& GetPointLight()
    {
        return m_Light;
    }

    void RenderPointLight(Shader shader)
    {
        m_Light.Render(shader);
    }

protected:
    PointLight m_Light;
    glm::vec3 m_LightColor;
};

#endif //OPENGLAPI_LAMP_H
