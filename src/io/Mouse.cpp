//
// Created by aeternum on 7/17/21.
//

#include "Mouse.h"

double Mouse::m_X = 0.0;
double Mouse::m_Y = 0.0;

double Mouse::m_LastX = 0.0;
double Mouse::m_LastY = 0.0;

double Mouse::m_DX = 0.0;
double Mouse::m_DY = 0.0;

double Mouse::m_ScrollDX = 0.0;
double Mouse::m_ScrollDY = 0.0;

bool Mouse::m_FirstMouse = true;

bool Mouse::m_Buttons[GLFW_MOUSE_BUTTON_LAST] = { false };
bool Mouse::m_ButtonsChanged[GLFW_MOUSE_BUTTON_LAST] = { false };

void Mouse::CursorCallback(GLFWwindow *window, double x, double y)
{
    m_X = x;
    m_Y = y;

    if (m_FirstMouse)
    {
        m_LastX = m_X;
        m_LastY = m_Y;
        m_FirstMouse = false;
    }

    m_DX = m_X - m_LastX;
    m_DY = m_LastY - m_Y; // inverted
    m_LastX = m_X;
    m_LastY = m_Y;
}

void Mouse::MouseButtonCallback(GLFWwindow *window, int button, int action, int mods)
{
    if (action != GLFW_RELEASE)
    {
        if (!m_Buttons[button])
            m_Buttons[button] = true;
    }
    else
        m_Buttons[button] = false;

    m_ButtonsChanged[button] = action != GLFW_REPEAT;
}

void Mouse::MouseWheelCallback(GLFWwindow *window, double dx, double dy)
{
    m_ScrollDX = dx;
    m_ScrollDY = dy;
}

double Mouse::GetMouseX()
{
    return m_X;
}

double Mouse::GetMouseY()
{
    return m_Y;
}

double Mouse::GetDX()
{
    return ReadOnce(m_DX);
}

double Mouse::GetDY()
{
    return ReadOnce(m_DY);
}

double Mouse::GetScrollDX()
{
    return ReadOnce(m_ScrollDX);
}

double Mouse::GetScrollDY()
{
    return ReadOnce(m_ScrollDY);
}

bool Mouse::Button(int button)
{
    return m_Buttons[button];
}

bool Mouse::ButtonChanged(int button)
{
    return ReadOnce(m_ButtonsChanged[button]);
}

bool Mouse::ButtonWentUp(int button)
{
    return !m_Buttons[button] && ButtonChanged(button);
}

bool Mouse::ButtonWentDown(int button)
{
    return m_Buttons[button] && ButtonChanged(button);
}

double Mouse::ReadOnce(double& value)
{
    double v = value;
    value = 0.0f;
    return v;
}

bool Mouse::ReadOnce(bool &value) {
    bool v = value;
    value = false;
    return v;
}

