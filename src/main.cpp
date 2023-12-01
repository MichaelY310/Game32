#include <GLUT/glut.h>
// #include "Render/Renderer.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h" 

#include <iostream>

GLuint texture;

// void display() {
//     Renderer::Init();
//     glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
//     // Renderer::DrawQuad({ 0.0, 0.0 }, 0.1, { 0.2, 0.3, 0.4 });
//     std::shared_ptr<Texture> texture = Texture::Create("Asset/yan.h");
//     Renderer::DrawQuad({ 0.0, 0.0 }, 0.1, texture);
//     Renderer::Flush();
// }

void loadTexture() {
    int width, height, channels;
    unsigned char* image = stbi_load("Asset/yan.png", &width, &height, &channels, 4);
    
    glGenTextures(1, &texture);
    
    // glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
    glBindTexture(GL_TEXTURE_2D,0);
    // glGenerateMipmap(GL_TEXTURE_2D);
   
    if (image) {
        stbi_image_free(image);
    }
    
}

void dis() {
    glClear(GL_COLOR_BUFFER_BIT |  GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);

    glBegin(GL_QUADS);
        // glColor3d(1,0,0);
        // glVertex2f(-1,-1);
        // glColor3d(1,1,0);
        // glVertex2f(1,-1);
        // glColor3d(1,1,0);
        // glVertex2f(1,1);
        // glColor3d(0,1,0);
        // glVertex2f(-1,1);

        glTexCoord2f(0.0f, 0.0f); glVertex2f(-0.5f, -0.5f); // Bottom-left vertex
        glTexCoord2f(1.0f, 0.0f); glVertex2f(0.5f, -0.5f);   // Bottom-right vertex
        glTexCoord2f(1.0f, 1.0f); glVertex2f(0.5f, 0.5f);    // Top-right vertex
        glTexCoord2f(0.0f, 1.0f); glVertex2f(-0.5f, 0.5f);  // Top-left vertex

        // glVertex2f(0.0, 5.0);
        // glVertex2f(4.0, -3.0);
        // glVertex2f(-4.0, -3.0);

    glEnd();

    glDisable(GL_TEXTURE_2D);

    // glFlush();

    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0,0,(GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-10,10,-10,10);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    // glutInit(&argc, argv);
    // glutInitDisplayMode(GLUT_RGB);
    // glutInitWindowPosition(100,200);
    // glutInitWindowSize(600, 600);

    // glutCreateWindow("Torry");

    // // loadTexture();

    // glutDisplayFunc(dis);
    // glutReshapeFunc(reshape);
    // glClearColor(0.0, 0.0, 0.0, 1.0);
    // // loadTexture();

    // glDeleteTextures(1,&texture);
   
    // glutMainLoop();
   
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE); // Use GLUT_DOUBLE for double buffering
    glutInitWindowPosition(100, 200);
    glutInitWindowSize(500, 500);

    glutCreateWindow("Torry");

    glutDisplayFunc(dis);
    glutReshapeFunc(reshape);
    glClearColor(0.0, 0.0, 0.0, 1.0);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);

    loadTexture();

    glutMainLoop();


    // glutInit(&argc, argv);
    // glutInitWindowSize(800, 600);
    // glutCreateWindow("GameTorry");
    // glutDisplayFunc(display);
    // glutMainLoop();

    return 0;
}



