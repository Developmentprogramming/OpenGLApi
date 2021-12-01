//
// Created by aeternum on 8/12/21.
//

#ifndef OPENGLAPI_MODELARRAY_H
#define OPENGLAPI_MODELARRAY_H

#include <vector>
#include "../../physics/RigidBody.h"

template <typename T, typename ... Args>
class ModelArray
{
public:
    explicit ModelArray(Args ... args)
        : m_Model(std::forward<Args>(args)...)
    {
    }

    virtual void Render(Shader shader, float dt)
    {
        for (auto& ins : m_Instances)
        {
            ins.Update(dt);
            m_Model.SetPos(ins.GetPos());
            m_Model.Render(shader, dt);
        }
    }

    void SetSize(glm::vec3 size)
    {
        m_Model.SetSize(size);
    }

    void CleanUp()
    {
        m_Model.CleanUp();
    }

    void PushInstance(RigidBody rigidBody)
    {
        m_Instances.push_back(rigidBody);
    }

    T& GetModel()
    {
        return m_Model;
    }

protected:
    T m_Model;
    std::vector<RigidBody> m_Instances;
};

#endif //OPENGLAPI_MODELARRAY_H
