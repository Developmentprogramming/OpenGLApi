//
// Created by aeternum on 7/17/21.
//

#ifndef OPENGLAPI_MOUSE_H
#define OPENGLAPI_MOUSE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Mouse
{
public:
    static void CursorCallback(GLFWwindow* window, double x, double y);
    static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
    static void MouseWheelCallback(GLFWwindow* window, double dx, double dy);

    static double GetMouseX();
    static double GetMouseY();

    static double GetDX();
    static double GetDY();

    static double GetScrollDX();
    static double GetScrollDY();

    static bool Button(int button);
    static bool ButtonChanged(int button);
    static bool ButtonWentUp(int button);
    static bool ButtonWentDown(int button);

protected:
    static double ReadOnce(double& value);
    static bool ReadOnce(bool& value);

private:
    static double m_X;
    static double m_Y;

    static double m_LastX;
    static double m_LastY;

    static double m_DX;
    static double m_DY;

    static double m_ScrollDX;
    static double m_ScrollDY;

    static bool m_FirstMouse;

    static bool m_Buttons[];
    static bool m_ButtonsChanged[];

};

#endif //OPENGLAPI_MOUSE_H
