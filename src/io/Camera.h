//
// Created by aeternum on 7/20/21.
//

#ifndef OPENGLAPI_CAMERA_H
#define OPENGLAPI_CAMERA_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

enum class CameraDirection
{
    NONE = 0,
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

class Camera
{
public:
    Camera(glm::vec3 position);

    void UpdateCameraPosition(double dx, double dy);
    void UpdateCameraDir(CameraDirection dir, double deltaTime);
    void UpdateCameraZoom(double dy);

    glm::mat4 GetViewMatrix();

    float GetZoom() const;

protected:
    glm::vec3 m_CameraPos;

    glm::vec3 m_CameraFront;
    glm::vec3 m_CameraUp;
    glm::vec3 m_CameraRight;

    glm::vec3 m_WorldUp;

    float m_Yaw;
    float m_Pitch;
    float m_Speed;
    float m_Zoom;

private:
    void UpdateCameraVectors();

};

#endif //OPENGLAPI_CAMERA_H
