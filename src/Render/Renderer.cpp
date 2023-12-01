#include <GL/glut.h>

#include "Renderer.h"

void Renderer::Init()
{   
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::Flush()
{   
    glFlush();
    glutSwapBuffers();
}

void Renderer::DrawQuad(vec2 position, double scale, vec3 color)
{
    // d c
    // a b
    vec2 a(-0.5, -0.5);
    vec2 b(0.5, -0.5);
    vec2 c(0.5, 0.5);
    vec2 d(-0.5, 0.5);

    a = a * scale;
    b = b * scale;
    c = c * scale;
    d = d * scale;

    a = a + position;
    b = b + position;
    c = c + position;
    d = d + position;

    glBegin(GL_QUADS);
    glColor3f(color.x, color.y, color.z); // Red
    glVertex2f(a.x, a.y);
    glVertex2f(b.x, b.y);
    glVertex2f(c.x, c.y);
    glVertex2f(d.x, d.y);

    glEnd();
}


void Renderer::DrawQuad(vec2 position, double scale, std::shared_ptr<Texture> texture)
{
    
    // d c
    // a b
    vec2 a(-0.5, -0.5);
    vec2 b(0.5, -0.5);
    vec2 c(0.5, 0.5);
    vec2 d(-0.5, 0.5);

    a = a * scale;
    b = b * scale;
    c = c * scale;
    d = d * scale;

    a = a + position;
    b = b + position;
    c = c + position;
    d = d + position;

    glBindTexture(GL_TEXTURE_2D, texture->m_RendererID);

    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex2f(a.x, a.y);
    glTexCoord2f(1.0f, 0.0f);
    glVertex2f(b.x, b.y);
    glTexCoord2f(1.0f, 1.0f);
    glVertex2f(c.x, c.y);
    glTexCoord2f(0.0f, 1.0f);
    glVertex2f(d.x, d.y);

    // glBindTexture(GL_TEXTURE_2D, 0);

    glEnd();
}