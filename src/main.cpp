#include <GL/glut.h>
#include <chrono>
#include <iostream>

#include "Scene/Scene.h"
#include "Render/Renderer.h"
#include "Core/Input.h"


Scene scene;
double deltaTime;
auto lastTime = std::chrono::high_resolution_clock::now();

void idle() {
    auto currentTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> fs = currentTime - lastTime;
    deltaTime = fs.count();
    lastTime = currentTime;

    scene.OnUpdate(deltaTime);
}

void display() {
    idle();
    scene.OnDisplay();
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

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(display);
    glutKeyboardFunc(Input::keyboardDownCallback);
    glutKeyboardUpFunc(Input::keyboardUpCallback);
    glutSpecialFunc(Input::specialKeyCallback);
    glutSpecialUpFunc(Input::specialKeyUpCallback);


    glutMainLoop();

    return 0;
}