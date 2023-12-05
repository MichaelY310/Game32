#pragma once

// #include <GLUT/glut.h>
#include <GL/glut.h>
#include <functional>

#include "Render/Renderer.h"

#define BIND_FUNCTION(fn) std::bind(&fn, this, std::placeholders::_1)

class Application
{
public:
    Application();
    ~Application() = default;

    void run(int argc, char** argv);
    void GlutDisplayFunc();
    void WindowResizeFunc(int width, int height);

    std::shared_ptr<Texture> m_Texture1;
};