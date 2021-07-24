//
// Created by aeternum on 7/16/21.
//

#ifndef OPENGLAPI_SHADER_H
#define OPENGLAPI_SHADER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>

class Shader
{
public:
    struct Sources
    {
        std::string vertexShaderSrc;
        std::string fragmentShaderSrc;
    };

    Shader(const std::string& shaderPath, const std::string& shadersRequirementsPath = "/home/aeternum/CLionProjects/OpenGLApi/assets/shaders");
    void Activate();

    // uniform functions
    void SetBool(const std::string& name, bool val);
    void SetInt(const std::string& name, int val);
    void SetFloat(const std::string& name, float val);
    void Set4Float(const std::string& name, float v1, float v2, float v3, float v4);
    void SetMat4(const std::string& name, glm::mat4 val);

protected:
    // utility functions
    Shader::Sources ParseShader(const std::string& path);
    unsigned int CreateShader(GLenum type, const std::string& source);
    static std::vector<std::string> LoadShaderRequirements(const std::string& shader_dir);
    static std::string ParseShaderSrc(const std::string& shader_file);
    static bool Search(std::vector<std::string> words, std::vector<std::string> value);

private:
    std::vector<std::string> m_ShaderRequirements;
    unsigned int m_Id;
};

#endif //OPENGLAPI_SHADER_H
