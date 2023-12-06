#include <iostream>
#include <filesystem>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "Texture.h"

Texture::Texture(const char* filePath)
{
    stbi_set_flip_vertically_on_load(true);

    std::filesystem::path currentPath = std::filesystem::current_path();
    std::string modifiedPath = currentPath.string();
    modifiedPath = modifiedPath.substr(0, modifiedPath.size() - 5);
    std::string finalPath = modifiedPath + "src/Asset/" + filePath;

    std::cout << finalPath << std::endl;



    int width, height, channels;
    // unsigned char* image = stbi_load(filePath, &width, &height, &channels, 0);
    stbi_uc* image = stbi_load(finalPath.c_str(), &width, &height, &channels, 0);

    if (!image) { std::cout << "failed to create texture" << std::endl; }
    if (image) { std::cout << "create texture" << std::endl; }

    GLenum internalFormat;
    GLenum dataFormat;
    if (channels == 4)
    {
        internalFormat = GL_RGBA8;
        dataFormat = GL_RGBA;
    } 
    else if (channels == 3)
    {
        internalFormat = GL_RGB8;
        dataFormat = GL_RGB;
    }
    else{ std::cout << "unsupported channels" << std::endl; }


    glGenTextures(1, &m_RendererID);
    glBindTexture(GL_TEXTURE_2D, m_RendererID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);


    glTexImage2D(GL_TEXTURE_2D, 0, dataFormat, width, height, 0, dataFormat, GL_UNSIGNED_BYTE, image);
    stbi_image_free(image);
}

std::shared_ptr<Texture> Texture::Create(const char* filePath)
{
    return std::make_shared<Texture>(filePath);
}