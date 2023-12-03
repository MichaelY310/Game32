#include <GL/glut.h>
#include <chrono>
#include <iostream>
#include <thread>

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

void sceneDisplay() {
    scene.OnDisplay();
}

void display() {
    idle();
    scene.OnDisplay();

    // std::thread updateThread(idle);
    // std::thread displayThread(sceneDisplay);

    // updateThread.join();
    // displayThread.join();
}

void reshape(int width, int height) {
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if (width <= height) {
        glOrtho(-1.0, 1.0, -1.0 * (GLfloat)height / width, 1.0 * (GLfloat)height / width, -100000.0, 100000.0);
    } else {
        glOrtho(-1.0 * (GLfloat)width / height, 1.0 * (GLfloat)width / height, -1.0, 1.0, -100000.0, 100000.0);
    }

    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Game32");

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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