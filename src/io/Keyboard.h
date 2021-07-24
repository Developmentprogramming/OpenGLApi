//
// Created by aeternum on 7/16/21.
//

#ifndef OPENGLAPI_KEYBOARD_H
#define OPENGLAPI_KEYBOARD_H

#include <GLFW/glfw3.h>

class Keyboard
{
public:
    static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

    static bool Key(int key);
    static bool KeyChanged(int key);
    static bool KeyWentUp(int key);
    static bool KeyWentDown(int key);

private:
    static bool m_Keys[];
    static bool m_KeysChanged[];
};

#endif //OPENGLAPI_KEYBOARD_H
