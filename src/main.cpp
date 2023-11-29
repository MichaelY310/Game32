#include <GL/glut.h>
#include "Render/Renderer.h"

std::shared_ptr<Texture> texture;

void display() {
    // Set up the camera position and orientation
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 1.0,  // Camera position
              0.0, 0.0, 0.0,   // Look at the origin
              0.0, 1.0, 0.0);   // Up vector

    Renderer::Init();
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    // Renderer::DrawQuad({ 0.0, 0.0 }, 0.1, { 0.2, 0.3, 0.4 });
    Renderer::DrawQuad({ 0.0, 0.0 }, 0.1, texture);
    Renderer::Flush();
}

void reshape(int width, int height) {
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if (width <= height) {
        glOrtho(-1.0, 1.0, -1.0 * (GLfloat)height / width, 1.0 * (GLfloat)height / width, -1.0, 1.0);
    } else {
        glOrtho(-1.0 * (GLfloat)width / height, 1.0 * (GLfloat)width / height, -1.0, 1.0, -1.0, 1.0);
    }

    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Game32");

    glEnable(GL_DEPTH_TEST);

    texture = Texture::Create("C:/Users/86166/Desktop/cs32/Game32/src/Asset/yan.jpg");

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    glutMainLoop();

    return 0;
}