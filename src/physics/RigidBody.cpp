//
// Created by aeternum on 8/12/21.
//

#include "RigidBody.h"

#include <cmath>

RigidBody::RigidBody(glm::vec3 pos, float mass, glm::vec3 velocity, glm::vec3 acceleration)
    : m_Pos(pos), m_Mass(mass), m_Velocity(velocity), m_Acceleration(acceleration)
{
}

void RigidBody::Update(float dt)
{
    m_Pos += m_Velocity * dt + 0.5f * m_Acceleration * (dt * dt);
    m_Velocity += m_Acceleration * dt;
}

void RigidBody::ApplyForce(glm::vec3 force)
{
    m_Acceleration += force / m_Mass;
}

void RigidBody::ApplyForce(glm::vec3 direction, float magnitude)
{
    ApplyForce(direction * magnitude);
}

void RigidBody::ApplyAcceleration(glm::vec3 acceleration)
{
    m_Acceleration += acceleration;
}

void RigidBody::ApplyAcceleration(glm::vec3 direction, float magnitude)
{
    ApplyAcceleration(direction * magnitude);
}

void RigidBody::ApplyImpulse(glm::vec3 force, float dt)
{
    m_Velocity += force / m_Mass * dt;
}

void RigidBody::ApplyImpulse(glm::vec3 direction, float magnitude, float dt)
{
    ApplyImpulse(direction * magnitude, dt);
}

void RigidBody::TransferEnergy(float joules)
{
    if (joules == 0)
        return;

    float deltaV = std::sqrt(2 * std::abs(joules) / m_Mass);
    m_Velocity += joules > 0 ? deltaV : -deltaV;
}

void RigidBody::SetPos(glm::vec3 pos)
{
    m_Pos = pos;
}

glm::vec3 &RigidBody::GetPos()
{
    return m_Pos;
}
