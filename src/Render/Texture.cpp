#include <GL/glut.h>
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "Texture.h"

Texture::Texture(const char* filePath)
{
    int width, height, channels;
    stbi_uc* image = stbi_load(filePath, &width, &height, &channels, 0);

    if (!image) { std::cout << "file not found" << std::endl; }

    glGenTextures(1, &m_RendererID);
    glBindTexture(GL_TEXTURE_2D, m_RendererID);

    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    GLenum internalFormat;
    GLenum dataFormat;

    if (channels == 4)
    {
        internalFormat = GL_RGBA;
        dataFormat = GL_RGBA;
    } 
    else if (channels == 3)
    {
        internalFormat = GL_RGB;
        dataFormat = GL_RGB;
    }

    glTexImage2D(GL_TEXTURE_2D, 0, dataFormat, width, height, 0, dataFormat, GL_UNSIGNED_BYTE, image);

    glBindTexture(GL_TEXTURE_2D, 0);
    stbi_image_free(image);

    std::cout << "m_RendererID "<<m_RendererID<<std::endl; 
}

std::shared_ptr<Texture> Texture::Create(const char* filePath)
{
    return std::make_shared<Texture>(filePath);
}