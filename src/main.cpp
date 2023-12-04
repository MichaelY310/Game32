#include <GLUT/glut.h>
// #include <GL/glut.h>
#include <chrono>
#include <iostream>
#include <thread>
#include <filesystem>

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
    sceneDisplay();
    idle();
    scene.OnDisplay();

    // Renderer::Init();
    // glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    // std::shared_ptr<Texture> texture = Texture::Create("wall.jpg");
    // std::shared_ptr<Entity> playerBullet = std::make_shared<Entity>(EntityType::PLAYER_BULLET, vec2(0.0, 0.0), 90.0f, 0.5, vec3(0.5, 0.5, 0.8), 1.0, 70.0, texture);
    // Renderer::DrawQuad(playerBullet);
    // Renderer::Flush();
}


void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    
    // glViewport(0, 0, 10, 10);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if (width <= height) {
        glOrtho(-1.0, 1.0, -1.0 * (GLfloat)height / width, 1.0 * (GLfloat)height / width, -100000.0, 100000.0);
    } else {
        glOrtho(-1.0 * (GLfloat)width / height, 1.0 * (GLfloat)width / height, -1.0, 1.0, -100000.0, 100000.0);
    }
    // gluOrtho2D(-1,1,-1,1);


    glMatrixMode(GL_MODELVIEW);
}

void Game_Menu(int id) 
{  
    // std::cout << "runnin g" <<std::endl;
    if (id == 2)
    {
        exit(1);
    }
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    // std::cout << "e231" <<std::endl;
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

    // glutCreateMenu(Game_Menu);
    // glutAddMenuEntry("START",1);
    // glutAddMenuEntry("QUIT",2);
    // glutAddMenuEntry("TEST",3);
    // glutAttachMenu(GLUT_RIGHT_BUTTON);


    glutMainLoop();


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