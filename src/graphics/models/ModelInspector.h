//
// Created by aeternum on 8/1/21.
//

#ifndef OPENGLAPI_MODELINSPECTOR_H
#define OPENGLAPI_MODELINSPECTOR_H

#include "../Model.h"

class ModelInspector : public Model
{
public:
    ModelInspector()
        : Model(glm::vec3(0.0f), glm::vec3(0.0095f))
    {
        LoadModel("/home/aeternum/Downloads/model_inspector/scene.gltf");
    }

    void Render(Shader shader, float dt) override
    {
        Rotate(glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));

        Model::Render(shader, dt);
    }

};

#endif //OPENGLAPI_MODELINSPECTOR_H
