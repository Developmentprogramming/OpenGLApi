//
// Created by aeternum on 7/16/21.
//

#include "Keyboard.h"

bool Keyboard::m_Keys[GLFW_KEY_LAST] = { false };
bool Keyboard::m_KeysChanged[GLFW_KEY_LAST] = { false };

void Keyboard::KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (action != GLFW_RELEASE)
    {
        if (!m_Keys[key])
            m_Keys[key] = true;
    }
    else
        m_Keys[key] = false;

    m_KeysChanged[key] = action != GLFW_REPEAT;
}

bool Keyboard::Key(int key)
{
    return m_Keys[key];
}

bool Keyboard::KeyChanged(int key)
{
    bool ret = m_KeysChanged[key];
    m_KeysChanged[key] = false;
    return ret;
}

bool Keyboard::KeyWentUp(int key)
{
    return !m_Keys[key] && KeyChanged(key);
}

bool Keyboard::KeyWentDown(int key)
{
    return m_Keys[key] && KeyChanged(key);
}

