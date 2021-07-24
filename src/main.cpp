#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>

#include "graphics/Shader.h"
#include "io/Keyboard.h"
#include "io/Camera.h"
#include "io/Mouse.h"
#include "graphics/Texture.h"
#include "graphics/models/Cube.h"

static Camera mainCamera(glm::vec3(0.0f, 0.0f, 5.0f));

void err_callback(int err_code, const char* msg)
{
    std::cout << "[GLFW error(" << err_code << ")]: " << msg << std::endl;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window, float dt)
{
    if (Keyboard::Key(GLFW_KEY_ESCAPE))
        glfwSetWindowShouldClose(window, true);

    // Keyboard inputs
    if (Keyboard::Key(GLFW_KEY_W))
        mainCamera.UpdateCameraDir(CameraDirection::FORWARD, dt);

    if (Keyboard::Key(GLFW_KEY_S))
        mainCamera.UpdateCameraDir(CameraDirection::BACKWARD, dt);

    if (Keyboard::Key(GLFW_KEY_A))
        mainCamera.UpdateCameraDir(CameraDirection::LEFT, dt);

    if (Keyboard::Key(GLFW_KEY_D))
        mainCamera.UpdateCameraDir(CameraDirection::RIGHT, dt);

    if (Keyboard::Key(GLFW_KEY_SPACE))
        mainCamera.UpdateCameraDir(CameraDirection::UP, dt);

    if (Keyboard::Key(GLFW_KEY_LEFT_SHIFT))
        mainCamera.UpdateCameraDir(CameraDirection::DOWN, dt);

    // Mouse inputs
    double dx = Mouse::GetDX(), dy = Mouse::GetDY();
    if (dx != 0.0 || dy != 0.0)
        mainCamera.UpdateCameraPosition(dx, dy);

    auto scrollDy = Mouse::GetScrollDY();
    if (scrollDy != 0.0)
        mainCamera.UpdateCameraZoom(scrollDy);
}

int main()
{
    glfwInit();

    glfwSetErrorCallback(err_callback);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

//    auto mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL", nullptr, nullptr);
    if (!window)
    {
        std::cout << "Unable to create glfw window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        std::cout << "Unable to initialize GLAD!" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Input Callbacks
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(window, Keyboard::KeyCallback);
    glfwSetCursorPosCallback(window, Mouse::CursorCallback);
    glfwSetMouseButtonCallback(window, Mouse::MouseButtonCallback);
    glfwSetScrollCallback(window, Mouse::MouseWheelCallback);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glEnable(GL_DEPTH_TEST);

    glViewport(0, 0, 800, 600);

//    float vertices[] =
//            {
//                    -0.5f, -0.5f, -0.5f,  0.101, 0.737, 0.611,
//                     0.5f, -0.5f, -0.5f,  0.101, 0.737, 0.611,
//                     0.5f,  0.5f, -0.5f,  0.101, 0.737, 0.611,
//                     0.5f,  0.5f, -0.5f,  0.101, 0.737, 0.611,
//                    -0.5f,  0.5f, -0.5f,  0.101, 0.737, 0.611,
//                    -0.5f, -0.5f, -0.5f,  0.101, 0.737, 0.611,
//
//                    -0.5f, -0.5f,  0.5f,  0.203, 0.596, 0.858,
//                     0.5f, -0.5f,  0.5f,  0.203, 0.596, 0.858,
//                     0.5f,  0.5f,  0.5f,  0.203, 0.596, 0.858,
//                     0.5f,  0.5f,  0.5f,  0.203, 0.596, 0.858,
//                    -0.5f,  0.5f,  0.5f,  0.203, 0.596, 0.858,
//                    -0.5f, -0.5f,  0.5f,  0.203, 0.596, 0.858,
//
//                    -0.5f,  0.5f,  0.5f,  0.945, 0.768, 0.058,
//                    -0.5f,  0.5f, -0.5f,  0.945, 0.768, 0.058,
//                    -0.5f, -0.5f, -0.5f,  0.945, 0.768, 0.058,
//                    -0.5f, -0.5f, -0.5f,  0.945, 0.768, 0.058,
//                    -0.5f, -0.5f,  0.5f,  0.945, 0.768, 0.058,
//                    -0.5f,  0.5f,  0.5f,  0.945, 0.768, 0.058,
//
//                     0.5f,  0.5f,  0.5f,  0.905, 0.298, 0.235,
//                     0.5f,  0.5f, -0.5f,  0.905, 0.298, 0.235,
//                     0.5f, -0.5f, -0.5f,  0.905, 0.298, 0.235,
//                     0.5f, -0.5f, -0.5f,  0.905, 0.298, 0.235,
//                     0.5f, -0.5f,  0.5f,  0.905, 0.298, 0.235,
//                     0.5f,  0.5f,  0.5f,  0.905, 0.298, 0.235,
//
//                    -0.5f, -0.5f, -0.5f,  0.607, 0.349, 0.713,
//                     0.5f, -0.5f, -0.5f,  0.607, 0.349, 0.713,
//                     0.5f, -0.5f,  0.5f,  0.607, 0.349, 0.713,
//                     0.5f, -0.5f,  0.5f,  0.607, 0.349, 0.713,
//                    -0.5f, -0.5f,  0.5f,  0.607, 0.349, 0.713,
//                    -0.5f, -0.5f, -0.5f,  0.607, 0.349, 0.713,
//
//                    -0.5f,  0.5f, -0.5f,  0.203, 0.286, 0.368,
//                     0.5f,  0.5f, -0.5f,  0.203, 0.286, 0.368,
//                     0.5f,  0.5f,  0.5f,  0.203, 0.286, 0.368,
//                     0.5f,  0.5f,  0.5f,  0.203, 0.286, 0.368,
//                    -0.5f,  0.5f,  0.5f,  0.203, 0.286, 0.368,
//                    -0.5f,  0.5f, -0.5f,  0.203, 0.286, 0.368
// //==========================================================================================================
//                    -0.5f, -0.5f, -0.5f,	0.0f, 0.0f,
//                     0.5f, -0.5f, -0.5f,	1.0f, 0.0f,
//                     0.5f,  0.5f, -0.5f,	1.0f, 1.0f,
//                     0.5f,  0.5f, -0.5f,	1.0f, 1.0f,
//                    -0.5f,  0.5f, -0.5f,	0.0f, 1.0f,
//                    -0.5f, -0.5f, -0.5f,	0.0f, 0.0f,
//
//                    -0.5f, -0.5f,  0.5f,	0.0f, 0.0f,
//                     0.5f, -0.5f,  0.5f,	1.0f, 0.0f,
//                     0.5f,  0.5f,  0.5f,	1.0f, 1.0f,
//                     0.5f,  0.5f,  0.5f,	1.0f, 1.0f,
//                    -0.5f,  0.5f,  0.5f,	0.0f, 1.0f,
//                    -0.5f, -0.5f,  0.5f,	0.0f, 0.0f,
//
//                    -0.5f,  0.5f,  0.5f,	1.0f, 0.0f,
//                    -0.5f,  0.5f, -0.5f,	1.0f, 1.0f,
//                    -0.5f, -0.5f, -0.5f,	0.0f, 1.0f,
//                    -0.5f, -0.5f, -0.5f,	0.0f, 1.0f,
//                    -0.5f, -0.5f,  0.5f,	0.0f, 0.0f,
//                    -0.5f,  0.5f,  0.5f,	1.0f, 0.0f,
//
//                     0.5f,  0.5f,  0.5f,	1.0f, 0.0f,
//                     0.5f,  0.5f, -0.5f,	1.0f, 1.0f,
//                     0.5f, -0.5f, -0.5f,	0.0f, 1.0f,
//                     0.5f, -0.5f, -0.5f,	0.0f, 1.0f,
//                     0.5f, -0.5f,  0.5f,	0.0f, 0.0f,
//                     0.5f,  0.5f,  0.5f,	1.0f, 0.0f,
//
//                    -0.5f, -0.5f, -0.5f,	0.0f, 1.0f,
//                     0.5f, -0.5f, -0.5f,	1.0f, 1.0f,
//                     0.5f, -0.5f,  0.5f,	1.0f, 0.0f,
//                     0.5f, -0.5f,  0.5f,	1.0f, 0.0f,
//                    -0.5f, -0.5f,  0.5f,	0.0f, 0.0f,
//                    -0.5f, -0.5f, -0.5f,	0.0f, 1.0f,
//
//                    -0.5f,  0.5f, -0.5f,	0.0f, 1.0f,
//                     0.5f,  0.5f, -0.5f,	1.0f, 1.0f,
//                     0.5f,  0.5f,  0.5f,	1.0f, 0.0f,
//                     0.5f,  0.5f,  0.5f,	1.0f, 0.0f,
//                    -0.5f,  0.5f,  0.5f,	0.0f, 0.0f,
//                    -0.5f,  0.5f, -0.5f,	0.0f, 1.0f
//            };

    Shader shader("/home/aeternum/CLionProjects/OpenGLApi/assets/shaders/Basic.shader.glsl");

    Cube cube(glm::vec3(0.0f), glm::vec3(1.0f));
    cube.Init();

    float lastFrame = 0.0f, deltaTime = 0.0f;
    while(!glfwWindowShouldClose(window))
    {
        auto currentTime = (float)glfwGetTime();
        deltaTime = currentTime - lastFrame;
        lastFrame = currentTime;
        processInput(window, deltaTime);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.090f, 0.090f, 0.090f, 1.0f);

        shader.Activate();

        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);

        view = mainCamera.GetViewMatrix();
        projection = glm::perspective(glm::radians(mainCamera.GetZoom()), (float)800/600, 1.0f, 100.0f);

        shader.SetMat4("view", view);
        shader.SetMat4("projection", projection);

        cube.Render(shader);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    cube.CleanUp();
    glfwTerminate();

    return 0;
}
