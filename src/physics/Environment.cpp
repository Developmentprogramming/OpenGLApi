//
// Created by aeternum on 8/12/21.
//

#include "Environment.h"

glm::vec3 Environment::m_GravitationalAcceleration = glm::vec3(0.0f, -9.8f, 0.0f);

glm::vec3 &Environment::GetGravitationalAcceleration()
{
    return m_GravitationalAcceleration;
}
