//
// Created by aeternum on 7/20/21.
//

#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include "Keyboard.h"

Camera::Camera(glm::vec3 position)
    : m_CameraPos(position), m_WorldUp(0.0f, 1.0f, 0.0f), m_Yaw(-90.5f),
    m_Pitch(0.0f), m_Speed(2.5f), m_Zoom(45.0f), m_CameraFront(0.0f, 0.0f, -1.0f)
{
    UpdateCameraVectors();
}

void Camera::UpdateCameraPosition(double dx, double dy)
{
    m_Yaw += dx;
    m_Pitch += dy;

    if (m_Pitch >= 89.0f)
        m_Pitch = 89.0f;
    else if (m_Pitch <= -89.0f)
        m_Pitch = -89.0f;

    UpdateCameraVectors();
}

void Camera::UpdateCameraDir(CameraDirection dir, double deltaTime)
{
    float velocity = (float)deltaTime * m_Speed;

    switch (dir)
    {
        case CameraDirection::NONE:
            break;
        case CameraDirection::FORWARD:
            m_CameraPos += m_CameraFront * velocity;
            break;
        case CameraDirection::BACKWARD:
            m_CameraPos -= m_CameraFront * velocity;
            break;
        case CameraDirection::LEFT:
            m_CameraPos -= m_CameraRight * velocity;
            break;
        case CameraDirection::RIGHT:
            m_CameraPos += m_CameraRight * velocity;
            break;
        case CameraDirection::UP:
            m_CameraPos += m_CameraUp * velocity;
            break;
        case CameraDirection::DOWN:
            m_CameraPos -= m_CameraUp * velocity;
            break;

        default:
            break;
    }
}

void Camera::UpdateCameraZoom(double dy)
{
    if (m_Zoom >= 1.0f && m_Zoom <= 45.0f)
        m_Zoom -= dy;
    else if (m_Zoom < 1.0f)
        m_Zoom = 1.0f;
    else
        m_Zoom = 45.0f;
}

glm::mat4 Camera::GetViewMatrix()
{
    return glm::lookAt(m_CameraPos, m_CameraPos + m_CameraFront, m_CameraUp);
}

void Camera::UpdateCameraVectors()
{
    glm::vec3 direction;
    direction.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
    direction.y = sin(glm::radians(m_Pitch));
    direction.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
    m_CameraFront = glm::normalize(direction);
    m_CameraRight = glm::normalize(glm::cross(m_CameraFront, m_WorldUp));
    m_CameraUp = glm::normalize(glm::cross(m_CameraRight, m_CameraFront));
}

float Camera::GetZoom() const
{
    return m_Zoom;
}
