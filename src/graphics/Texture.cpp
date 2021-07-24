//
// Created by aeternum on 7/20/21.
//

#include "Texture.h"

#include "stb/stb_image.h"
#include <iostream>

unsigned int Texture::m_CurrentId = 0;

Texture::Texture(const std::string &path, const std::string& name)
    : m_FilePath(path), m_TextureName(name),
    m_Width(0), m_Height(0), m_NChannels(0), m_Id(0), m_UId(m_CurrentId++),
    m_Buffer(nullptr)
{
    stbi_set_flip_vertically_on_load(true);
    m_Buffer = stbi_load(path.c_str(), &m_Width, &m_Height, &m_NChannels, 0);

    glGenTextures(1, &m_Id);
    glBindTexture(GL_TEXTURE_2D, m_Id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    GLenum colorMode = GL_RGB;

    switch (m_NChannels)
    {
        case 1:
            colorMode = GL_R;
            break;
        case 4:
            colorMode = GL_RGBA;
            break;

        default:
            break;
    }

    if (m_Buffer)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, colorMode, m_Width, m_Height, 0, colorMode, GL_UNSIGNED_BYTE, m_Buffer);
        stbi_image_free(m_Buffer);
    }

    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Bind(unsigned int slot) const
{
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, m_Id);
}

void Texture::Unbind() const
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

std::string& Texture::GetTextureName()
{
    return m_TextureName;
}

unsigned int& Texture::GetId()
{
    return m_UId;
}

void Texture::CleanUp()
{
    glDeleteTextures(1, &m_Id);
}
