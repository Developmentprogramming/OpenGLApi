//
// Created by aeternum on 7/20/21.
//

#ifndef OPENGLAPI_TEXTURE_H
#define OPENGLAPI_TEXTURE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

class Texture
{
public:
    Texture(const std::string& path, const std::string& name);

    void Bind(unsigned int slot = 0) const;
    void Unbind() const;

    std::string& GetTextureName();
    unsigned int& GetId();

    void CleanUp();

private:
    unsigned int m_Id, m_UId;
    int m_Width, m_Height, m_NChannels;
    std::string m_FilePath;
    std::string m_TextureName;
    unsigned char* m_Buffer;

    static unsigned int m_CurrentId;
};

#endif //OPENGLAPI_TEXTURE_H
