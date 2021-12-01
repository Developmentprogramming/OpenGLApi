//
// Created by aeternum on 8/12/21.
//

#ifndef OPENGLAPI_RIGIDBODY_H
#define OPENGLAPI_RIGIDBODY_H

#include <glm/glm.hpp>

class RigidBody
{
public:
    explicit RigidBody(glm::vec3 pos, float mass = 1.0f, glm::vec3 velocity = glm::vec3(0.0f), glm::vec3 acceleration = glm::vec3(0.0f));

    void Update(float dt);

    void ApplyForce(glm::vec3 force);
    void ApplyForce(glm::vec3 direction, float magnitude);

    void ApplyAcceleration(glm::vec3 acceleration);
    void ApplyAcceleration(glm::vec3 direction, float magnitude);

    void ApplyImpulse(glm::vec3 force, float dt);
    void ApplyImpulse(glm::vec3 direction, float magnitude, float dt);

    void TransferEnergy(float joules);

    void SetPos(glm::vec3 pos);
    glm::vec3 &GetPos();

protected:
    glm::vec3 m_Pos;

private:
    float m_Mass;
    glm::vec3 m_Velocity;
    glm::vec3 m_Acceleration;

};

#endif //OPENGLAPI_RIGIDBODY_H
