//
// Created by aeternum on 8/12/21.
//

#ifndef OPENGLAPI_ENVIRONMENT_H
#define OPENGLAPI_ENVIRONMENT_H

#include <glm/glm.hpp>

class Environment
{
public:
    static glm::vec3& GetGravitationalAcceleration();

private:
    static glm::vec3 m_GravitationalAcceleration;
};

#endif //OPENGLAPI_ENVIRONMENT_H
