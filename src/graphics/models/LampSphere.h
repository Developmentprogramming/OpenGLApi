//
// Created by aeternum on 8/12/21.
//

#ifndef OPENGLAPI_LAMPSPHERE_H
#define OPENGLAPI_LAMPSPHERE_H

#include "../Model.h"
#include "../Light.h"
#include "ModelArray.h"

class LampSphere : public Model
{
public:
    LampSphere(glm::vec3 lightColor, glm::vec3 pos, glm::vec3 size = glm::vec3(0.055f))
        : Model(pos, size, true),
        m_LightColor(lightColor),
        m_PointLight("pointLight", pos, glm::vec4(glm::vec3(0.05f), 1.0), glm::vec4(glm::vec3(0.8f), 1.0), glm::vec4(1.0))
    {
        LoadModel("/home/aeternum/Downloads/sphere/scene.gltf");
    }

    void Render(Shader shader, float dt) override
    {
        shader.Set3Float("lightColor", m_LightColor);

        Model::Render(shader, dt);
    }

    void RenderPointLight(Shader shader)
    {
        m_PointLight.Render(shader);
    }

    PointLight &GetPointLight()
    {
        return m_PointLight;
    }

protected:
    PointLight m_PointLight;
    glm::vec3 m_LightColor;

};

class LampSphereArray : public ModelArray<LampSphere, glm::vec3, glm::vec3>
{
public:
    LampSphereArray()
        : ModelArray(glm::vec3(1.0f), glm::vec3(0.0f))
    {
    }

    void Render(Shader shader, float dt) override
    {
        for (auto& light : m_LightInstances)
        {
            m_Model.Update(dt);
            m_Model.SetPos(light.GetPos());
            m_Model.Render(shader, dt);
        }
    }

    void RenderLights(Shader shader)
    {
        shader.SetInt("noOfPointLight", m_LightInstances.size());
        for (auto& light : m_LightInstances)
            light.Render(shader);
    }

    void PushLightInstance(PointLight pointLight)
    {
        m_LightInstances.push_back(pointLight);
    }

protected:
    std::vector<PointLight> m_LightInstances;
};

#endif //OPENGLAPI_LAMPSPHERE_H
