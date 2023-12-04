#pragma once

#include <memory>
// #include <GL/glut.h>
#include <GLUT/glut.h>
class Texture
{
public:
    Texture(const char* filePath);
    static std::shared_ptr<Texture> Create(const char* filePath);

    GLuint m_RendererID;
};