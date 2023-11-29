#include <GL/glut.h>
#include "Render/Renderer.h"

void display() {
    Renderer::Init();
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    // Renderer::DrawQuad({ 0.0, 0.0 }, 0.1, { 0.2, 0.3, 0.4 });
    std::shared_ptr<Texture> texture = Texture::Create("Asset/yan.h");
    Renderer::DrawQuad({ 0.0, 0.0 }, 0.1, texture);
    Renderer::Flush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Game32");
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}