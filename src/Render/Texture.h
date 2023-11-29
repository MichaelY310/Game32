#pragma once

#include <memory>

class Texture
{
public:
    Texture(const char* filePath);

    static std::shared_ptr<Texture> Create(const char* filePath);

    GLuint m_RendererID;
};