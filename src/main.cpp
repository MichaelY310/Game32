#include <GL/glut.h>
// #include <GLUT/glut.h>
#include <chrono>
#include <iostream>
#include <thread>

#include "Scene/Scene.h"
#include "Render/Renderer.h"
#include "Core/Input.h"


float xposition2 = -0.5; 
float xposition3 = 0.5; 
float yposition = -0.1;

int direction1 = 1;
int direction2 = -1;
int direction3 = 1;
int direction4 = 1;

void DrawBullet();
void timer(int );

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

float xposition1 = -0.7; 


void display() {
    idle();
    Renderer::Init();
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    scene.OnDisplay();
    DrawBullet();
    // std::thread updateThread(idle);
    // std::thread displayThread(sceneDisplay);

    // updateThread.join();
    // displayThread.join();
}


void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    
    // glViewport(0, 0, 10, 10);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if (width <= height) {
        glOrtho(-1.0, 1.0, -1.0 * (GLfloat)height / width, 1.0 * (GLfloat)height / width, -1.0, 1.0);
    } else {
        glOrtho(-1.0 * (GLfloat)width / height, 1.0 * (GLfloat)width / height, -1.0, 1.0, -1.0, 1.0);
    }
    // gluOrtho2D(-1,1,-1,1);


    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    // std::cout << "e231" <<std::endl;
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

    glutTimerFunc(0,timer,0);
    // glClearColor(0,0,0,1);
    glutMainLoop();


    // glutInit(&argc, argv);
    // glutInitWindowSize(800, 600);
    // glutCreateWindow("GameTorry");
    // glutDisplayFunc(display);
    // glutMainLoop();

    return 0;
}



void DrawBullet()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glPointSize(10.0);

    glBegin(GL_POINTS);
    glColor3f(1, 1, 0); // Red
    //   std::cout << xposition1 << " " <<xposition2 << " " <<xposition3 <<std::endl;
    glVertex2f(xposition1, -0.5);
    glVertex2f(xposition2, -0.3);
    glVertex2f(xposition3, 0.7);
    glVertex2f((xposition1 + xposition2 - xposition3)/2, yposition);
   

    glEnd();

    
    glutSwapBuffers();
    glFlush();
}

void timer(int )
{
    glutPostRedisplay();
    glutTimerFunc(1000/60, timer, 0);

    // std::cout << direction1 << " " <<xposition2 << " " <<xposition3 <<std::endl;
    switch(direction1)
    {
        case 1:
            if (xposition1 < 1) 
                // std::cout << "r" <<std::endl;
                xposition1 += 0.05;
            
            else 
                // std::cout << "r" <<std::endl;
                direction1 = -1;
            
            break;
        case -1:
            if (xposition1 > -1) 
                xposition1 -= 0.05;
            
            else 
                direction1 = 1;
            
            break;
    }

    switch(direction2)
    {
        case 1:
            if (xposition2 < 1) {
                // std::cout << "r" <<std::endl;
                xposition2 += 0.05;
            }
            else {
                direction2 = -1;
            }
            break;
        case -1:
            if (xposition2 > -1) {
                xposition2 -= 0.05;
            }
            else {
                direction2 = 1;
            }
            break;
    }

    switch(direction3)
    {
        case 1:
            if (xposition3 < 1) {
                // std::cout << "r" <<std::endl;
                xposition3 += 0.05;
            }
            else {
                direction3 = -1;
            }
            break;
        case -1:
            if (xposition3 > -1) {
                xposition3 -= 0.05;
            }
            else {
                direction3 = 1;
            }
            break;
    }

    switch(direction4)
    {
        case 1:
            if (yposition < 1) {
                // std::cout << "r" <<std::endl;
                yposition += 0.05;
            }
            else {
                direction4 = -1;
            }
            break;
        case -1:
            if (yposition > -1) {
                yposition -= 0.05;
            }
            else {
                direction4 = 1;
            }
            break;
    }

    
}