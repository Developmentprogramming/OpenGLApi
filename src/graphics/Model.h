//
// Created by aeternum on 7/21/21.
//

#ifndef OPENGLAPI_MODEL_H
#define OPENGLAPI_MODEL_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Mesh.h"

class Model
{
public:
    Model();

    virtual void Init() = 0;
    virtual void Render(Shader shader);
    void CleanUp();

    std::vector<Mesh>& GetMeshes();

protected:
    std::vector<Mesh> m_Meshes;

};


#endif //OPENGLAPI_MODEL_H
