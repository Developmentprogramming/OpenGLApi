//
// Created by aeternum on 7/16/21.
//

#include "Shader.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem>
#include <algorithm>
#include <glm/gtc/type_ptr.hpp>

namespace fs = std::filesystem;

Shader::Shader(const std::string& shaderPath, const std::string& shaderRequirementsPath)
    : m_ShaderRequirements(std::move(LoadShaderRequirements(shaderRequirementsPath)))
{
    m_Id = glCreateProgram();
    auto [ vertexShaderSrc, fragmentShaderSrc ] = ParseShader(shaderPath.c_str());
    unsigned int vs = CreateShader(GL_VERTEX_SHADER, vertexShaderSrc.c_str());
    unsigned int fs = CreateShader(GL_FRAGMENT_SHADER, fragmentShaderSrc.c_str());
    glAttachShader(m_Id, vs);
    glAttachShader(m_Id, fs);
    glLinkProgram(m_Id);
    glValidateProgram(m_Id);

    glDeleteShader(vs);
    glDeleteShader(fs);
}

void Shader::Activate()
{
    glUseProgram(m_Id);
}

Shader::Sources Shader::ParseShader(const std::string& path)
{
    std::ifstream file;
    std::stringstream ss[2];

    enum class ShaderType
    {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    file.open(path);
    ShaderType type = ShaderType::NONE;
    bool loadRequired = false;

    if (file.is_open())
    {
        std::string line;
        while(getline(file, line))
        {
            if (line.find("#shader") != std::string::npos)
            {
                if (line.find("vertex") != std::string::npos)
                    type = ShaderType::VERTEX;
                else if (line.find("fragment") != std::string::npos)
                    type = ShaderType::FRAGMENT;
            }
            else if (loadRequired)
            {
                for (auto& src : m_ShaderRequirements)
                    ss[(int)type] << src << '\n';

                loadRequired = false;
            }
            else
                ss[(int)type] << line << '\n';

            if (line.find("#version") != std::string::npos)
                loadRequired = true;
        }
    }
    else
        std::cout << "[Shader]: Unable to open the shader (" << path << ")!" << std::endl;

    file.close();
    return { ss[0].str(), ss[1].str() };
}

unsigned int Shader::CreateShader(GLenum type, const std::string& source)
{
    unsigned int shader = glCreateShader(type);
//    std::vector<GLchar*> src;
//    src.push_back((GLchar*)(source.c_str()));

//    for (auto& required_src : m_ShaderRequirements)
//        src.push_back((GLchar*)required_src.c_str());
    GLchar* src = (GLchar*)source.c_str();

    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);

    // check errors
    int status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (!status)
    {
        int length;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
        char* msg = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(shader, length, nullptr, msg);
        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader: \t" << msg << std::endl;
        glDeleteShader(shader);
        return 0;
    }

    return shader;
}

void Shader::SetBool(const std::string& name, bool val)
{
    SetInt(name, val);
}

void Shader::SetInt(const std::string &name, int val)
{
    glUniform1i(glGetUniformLocation(m_Id, name.c_str()), val);
}

void Shader::SetFloat(const std::string &name, float val)
{
    glUniform1f(glGetUniformLocation(m_Id, name.c_str()), val);
}

void Shader::Set4Float(const std::string &name, float v1, float v2, float v3, float v4)
{
    glUniform4f(glGetUniformLocation(m_Id, name.c_str()), v1, v2, v3, v4);
}

void Shader::SetMat4(const std::string &name, glm::mat4 val)
{
    glUniformMatrix4fv(glGetUniformLocation(m_Id, name.c_str()), 1, GL_FALSE, glm::value_ptr(val));
}

std::vector<std::string> Shader::LoadShaderRequirements(const std::string& shader_dir)
{
    std::vector<std::string> ret;
    for (auto& path : fs::recursive_directory_iterator(shader_dir))
    {
        if (path.path().extension() == ".glsl")
            ret.push_back(ParseShaderSrc(path.path().string()));
    }

    return ret;
}

std::string Shader::ParseShaderSrc(const std::string& shader_file)
{
    std::ifstream file(shader_file);

    std::string line, ret;
    bool inMain = false;
    if (file.is_open())
    {
        while(getline(file, line))
        {
            std::string word;
            std::vector<std::string> words;
            std::stringstream l(line);
            while (l >> word)
                words.push_back(word);

            if (Search(words, {"void", "main()"}))
                inMain = true;
            else if (inMain && (line.find('}') != std::string::npos))
            {
                inMain = false;
                continue;
            }

            if (Search(words, {"#shader"}) ||
                Search(words, {"#version"}) ||
                Search(words, {"layout"}) ||
                Search(words, {"uniform"}) ||
                Search(words, {"out"}) ||
                Search(words, {"in"}) ||
                inMain)
                continue;
            else
                ret += line + '\n';
        }
    }
    else
        std::cout << "Unable to load shader requirement (" << shader_file << std::endl;

    file.close();
    return std::move(ret);
}

bool Shader::Search(std::vector<std::string> words, std::vector<std::string> value)
{
    return std::search(words.begin(), words.end(), value.begin(), value.end()) != words.end();
}

